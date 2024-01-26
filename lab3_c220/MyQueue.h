#pragma once
#include <utility>
#include <initializer_list>
#include <iostream>

template <typename T>
class MyQueue
{
	T* m_p{}; // указатель на начало динамического массива
	size_t m_n{}; // актуальное количество элементов в очереди
	size_t m_cap{ 1 }; // емкость (сколько выделено памяти)
	size_t m_first{}; // индекс первого элемента в очереди (это тот элемент, который можно извлечь из очереди с помощью pop())
	size_t m_last{}; // индекс первого свободного элемента в очереди (это тот элемент, в который можно присвоить новое значение с помощью push())
	const size_t delta{ 1 }; // на сколько увеличиваем емкость при перераспределении памяти
public:
	class iterator {
		// данные и методы, реализующие функциональность итератора для кольцевой очереди
		const MyQueue* m_pQ; // итерируемая очередь
		int m_i; // индекс текущего элемента
	public:
		iterator(const iterator& other) :m_pQ(other.m_pQ), m_i(other.m_i) {}
		iterator(const MyQueue* q, size_t index):m_pQ(q),m_i(index){}
		// реализуем методы, которые использует range-based for
		iterator& operator++ () { m_i = (m_i + 1) % (m_pQ->m_cap); return *this; } // оператор префиксного инкремента
		T& operator* () { return m_pQ->m_p[m_i]; } // оператор разыменования
		bool operator!= (const iterator& other) const { return m_i != other.m_i; } // оператор сравнения
		// может быть потребуется что-то еще
	};
	iterator begin() const {return iterator{ this,m_first };} // итератор на начало очереди
	iterator end() const { return iterator{ this, m_last };	} // итератор на конец очереди
	// так как класс сложный, реализуем «джентльменский» набор:
	MyQueue();
	~MyQueue();
	MyQueue(const MyQueue&);
	MyQueue(std::initializer_list<T> l);
	MyQueue(size_t count, const T& t);
	MyQueue(MyQueue&&);
	MyQueue& operator= (const MyQueue&);
	MyQueue& operator= (MyQueue&&);
	MyQueue& operator=(std::initializer_list<T> l);
	
	// методы, реализующие функциональность очереди
	void push(const T& t);
	void push(T&& t_tmp);
	T pop();
	void printMyQueue();
	
		// а также, методы, необходимые для выполнения задания
};

template<typename T>
inline MyQueue<T>::MyQueue():m_p(new T[m_cap]) {}

template<typename T>
inline MyQueue<T>::~MyQueue()
{
	delete[] m_p;
	m_p = nullptr;
	m_n = m_first = m_last = 0;
	m_cap = 1;
}

template<typename T>
inline MyQueue<T>::MyQueue(const typename MyQueue<T>& other):m_p(new T[other.m_n + 1]), m_n(other.m_n), m_cap(other.m_n + 1)
{
	//Перезапись кругового буфера (копирование)
	//При перезаписи данных из старого динамического массива в новый данные	«разворачиваем», копируем от first_old до last_old.
	m_first = 0;
	m_last = m_n;//m_last = m_first + m_n
	for (size_t i = 0; i < m_n; i++)
		m_p[i] = other.m_p[(other.m_first + i) % other.m_cap];
}

template<typename T>
inline MyQueue<T>::MyQueue(std::initializer_list<T> l)
{
	m_cap = l.size() + 1;
	m_p = new T[m_cap];
	m_n = 0;
	for (auto&& i : l) this->push(i);
}

template<typename T>
inline MyQueue<T>::MyQueue(size_t count, const T& t)
{
	m_p = new T[count + delta];
	for (size_t i = 0; i < count; i++) m_p[i] = t;
	m_n = count;
	m_cap = count + delta;
	m_first = 0;
	m_last = count;
}

template<typename T>
inline MyQueue<T>::MyQueue(MyQueue&& other_tmp):m_p(other_tmp.m_p),m_n(other_tmp.m_n),m_cap(other_tmp.m_cap),m_first(other_tmp.m_first),m_last(other_tmp.m_last)
{
	other_tmp.m_cap = 1;
	other_tmp.m_n = 0;
	other_tmp.m_first = 0;
	other_tmp.m_last = 0;
	other_tmp.m_p = nullptr;
}

template<typename T>
inline  MyQueue<T>& MyQueue<T>::operator=(const  MyQueue<T>& other)
{
	if (&other != this)
	{
		m_n = other.m_n;
		if (m_n >= m_cap)
		{
			delete[] m_p;
			m_cap = other.m_n + 1;
			m_p = new T[m_cap];
		}
		m_first = 0;
		m_last = m_n;
		for(size_t i=0;i<m_n;i++) 
			m_p[i] = other.m_p[(other.m_first + i) % other.m_cap];
	}
	return *this;
}

template<typename T>
inline  MyQueue<T>& MyQueue<T>::operator=(typename MyQueue<T>&& other_tmp)
{
	if (this != &other_tmp)
	{
		m_n = other_tmp.m_n;
		m_cap = other_tmp.m_cap;
		m_first = other_tmp.m_first;
		m_last = other_tmp.m_last;
		delete[] m_p;
		m_p = other_tmp.m_p;
		other_tmp.m_p=nullptr;
		other_tmp.m_n = other_tmp.m_first = other_tmp.m_last = 0;
		other_tmp.m_cap = 1;
	}
	return *this;
}

template<typename T>
inline  MyQueue<T>& MyQueue<T>::operator=(std::initializer_list<T> l)
{
	m_n = l.size();
	if (m_n >= m_cap)
	{
		delete[] m_p;
		m_cap = m_n + 1;
		m_p = new T[m_cap];
	}
	m_first = 0;
	m_last = m_n;
	for (size_t i=0;auto& k:l)
	{
		m_p[i] = k;
		i++;
	}

return *this; 
}

template<typename T>
inline void MyQueue<T>::push(const T& t)
{
	if (m_n == m_cap - 1)
	{
		T* enlarged_p = new T[m_cap + delta];
		for (size_t i = 0; i < m_n; i++)
			enlarged_p[i] = std::move(m_p[(m_first + i) % m_cap]);
		delete[] m_p;
		m_p = enlarged_p;
		enlarged_p = nullptr;
		m_cap += delta;
		m_first = 0;
		m_last = m_n;
	}
	m_p[(m_first + m_n)%m_cap] = t;
	m_n++;
	m_last = (m_last + 1) % m_cap;
}

template<typename T>
inline void MyQueue<T>::push(T&& t_tmp)
{
	if (m_n == m_cap - 1)
	{
		T* enlarged_p = new T[m_cap + delta];
		for (size_t i = 0; i < m_n; i++)
			enlarged_p[i] = std::move(m_p[(m_first + i) % m_cap]);
		delete[] m_p;
		m_p = enlarged_p;
		enlarged_p = nullptr;
		m_cap += delta;
		m_first = 0;
		m_last = m_n;
	}
	m_p[(m_first + m_n) % m_cap] = std::move(t_tmp);
	m_n++;
	m_last = (m_last + 1) % m_cap;
}

template<typename T>
inline T MyQueue<T>::pop()
{
	T res{};
	if (m_n)
	{
		res = std::move(m_p[m_first]);
		m_first = (m_first + 1) % m_cap;
		m_n--;
		return res;

	}
	else throw std::out_of_range("My Queue is empty! Nothing to pop!");
}

template<typename T>
inline void MyQueue<T>::printMyQueue()
{
	std::cout << "\nRaw array:\n";
	for (size_t i = 0; i < m_cap; i++) std::cout << m_p[i] << " ";
	std::cout << "\nMy Queue:\n";
	for (const auto& el : *this) std::cout << el << " ";
}


