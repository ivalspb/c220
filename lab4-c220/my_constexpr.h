#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <type_traits>
#include <stack>
#include <queue>


constexpr int factr_cnstexpr(int t)
{
	return t > 0 ? t * factr_cnstexpr(t - 1) : 1;
}


constexpr int get_lenght_chars(const char* bin_char)
{
	return (*(bin_char + 1) == 0) ? 1 : get_lenght_chars(bin_char + 1) + 1;
}

constexpr int pow_of_2_const(int p)
{
	return
		(p == 0) ? 1 : 2 * pow_of_2_const(p - 1);
}

constexpr  int operator""_b(const char* bn_chrs)
{
	return
		(*(bn_chrs + 1) == 0) ?//если конец строки?
		(*bn_chrs == '1' ? 1 : 0) ://то это просто младший бит, определяющий четность и нечетность
		(*(bn_chrs)-'0')//либо берем текущий бит..
		* pow_of_2_const(get_lenght_chars(bn_chrs) - 1) //..умноженный на степень двойки порядка бита 
		+ operator""_b(bn_chrs + 1);//и берем рекурсивно следующий бит
}

std::string operator""_toBinStr(unsigned long long digit);

template <typename T>
void printContainer(T& t)
{
	std::cout << std::endl;
	if constexpr (std::is_pointer_v<std::remove_reference_t<decltype(*(std::begin(t)))>>)
		for (auto i=std::begin(t);i!=std::end(t);++i) 
			std::cout << **i << " ";
	else
		for (auto i = std::begin(t); i != std::end(t); ++i)
			std::cout << *i << " ";
}

template <typename T, typename U>
auto my_sum(const T& t, const U& u)
{
	if constexpr (std::is_same_v < std::vector<T>, U>)//U=vector<T>
	{
		U res = u;
		for (auto& i : res) i = i + t;
		return res;
	}
	else
	{
		if constexpr (std::is_same_v < std::vector<U>, T>)//T=vector<U>
		{
			T res = t;
			for (auto& i : res) i = i + u;
			return res;
		}
		else
		{
			decltype(t+u) res = t + u;
			return res;
		}
	}
}

template <typename AdapterContainer>
void printAdapterContainer(AdapterContainer c)
{
	std::cout << std::endl;
	if constexpr (std::is_same_v<std::queue<typename AdapterContainer::value_type, typename AdapterContainer::container_type>, AdapterContainer>)
	{
		if constexpr (std::is_pointer_v<std::remove_reference_t<decltype(c.front())>>)
		{
			while (!c.empty())
			{
				std::cout << *(c.front()) << " ";
				c.pop();
			}
		}
		else
		{
			while (!c.empty())
			{
				std::cout << c.front() << " ";
				c.pop();
			}
		}
	}
	else
	{
		if constexpr (std::is_pointer_v<std::remove_reference_t<decltype(c.top())>>)
		{
			while (!c.empty())
			{
				std::cout << *(c.top()) << " ";
				c.pop();
			}
		}
		else
		{
			while (!c.empty())
			{
				std::cout << c.top() << " ";
				c.pop();
			}
		}
	}
}

template <typename T>
constexpr T Smth()
{
	if constexpr (std::is_same_v<T, int>) return 1;
	else
	{
		if constexpr (std::is_same_v<T, double>) return 2.2;
		else
		{
			if constexpr (std::is_same_v<T, std::string>) return "abc";

		}
	}
	return T{};
}


template<typename T, size_t size> 
class MyArray
{
	T ar[size] = {}; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
public:
	constexpr MyArray() = default;
	/*constexpr MyArray(const T* source_ar, const size_t source_size):ar(source_ar)
	{
		if (!(source_size < size))
		{
			for (size_t i = 0; i < size; i++)
				ar[i] = source_ar[i];
		}
		else
		{
			for (size_t i = 0; i < source_size; i++)
				ar[i] = source_ar[i];
		}
	}*/
	constexpr MyArray(const T* source_ar)
	{
		for (size_t i = 0; i < size; i++)
			ar[i] = source_ar[i];
	}
};


//template <typename T, typename... U>
//MyArray(T, U...)->MyArray<T, 1 + sizeof...(U)>;

//template <typename T, size_t size>
//MyArray(const T*) -> MyArray<T, size>;

template <typename T, size_t size>
MyArray(const T(&ar)[size]) -> MyArray<T, size>;
