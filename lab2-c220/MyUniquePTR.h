//std::unique_ptr
#pragma once


template <typename T>
class MyUniquePTR
{
	T* mp;
public:
	MyUniquePTR() :mp(nullptr) {};
	MyUniquePTR(const MyUniquePTR<T>& other) = delete;
	MyUniquePTR(MyUniquePTR<T>&& tmp_other) :mp(std::move(tmp_other.mp)) { tmp_other.mp = nullptr; } 
	MyUniquePTR& operator=(const MyUniquePTR<T>& other)=delete;
	MyUniquePTR& operator=(MyUniquePTR<T>&& tmp_other);
	explicit MyUniquePTR(T* other_p);
	explicit MyUniquePTR(T&& tmp_p);
	explicit operator bool() const {return mp;}
	T& operator*() const { return *mp; }
	T* operator->() const {return mp;}
	//MyUniquePTR(const T* other_p);
	~MyUniquePTR(){delete mp;}
	MyUniquePTR& operator=(T* othet_p);
	T* get() const;
	void set(const T*);
	void release() noexcept;
	void reset();
};


template <typename T>
inline MyUniquePTR<T>& MyUniquePTR<T>::operator=(MyUniquePTR<T>&& tmp_other)
{
	if(this==tmp_other) return *this;
	if(mp) delete mp;
    mp=std::move(tmp_other.mp);
	tmp_other.mp=nullptr;
	return mp;
}

template<typename T>
inline MyUniquePTR<T>::MyUniquePTR(T* other_p)
{
	mp = other_p;
}

template<typename T>
inline MyUniquePTR<T>::MyUniquePTR(T&& tmp_p)
{
	mp = std::move(tmp_p);
}

template <typename T>
inline MyUniquePTR<T> &MyUniquePTR<T>::operator=(T *other_p)
{
    if (mp) delete mp;
	mp=other_p;

}

template <typename T>
inline T *MyUniquePTR<T>::get() const
{
    return mp;
}

template <typename T>
inline void MyUniquePTR<T>::set(const T * other)
{
	if(mp) delete mp;
	mp=other;
}

template <typename T>
inline void MyUniquePTR<T>::release() noexcept
{
	T* res_p=nullptr;
	std::swap(res_p,mp);
	return res_p;
}

template <typename T>
inline void MyUniquePTR<T>::reset()
{
	T* tmp=release();
	delete tmp;
}


