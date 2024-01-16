#pragma once
#include <vector>
#include <initializer_list>
#include <iterator>

template <typename T, typename Compare=std::less>
class UnicVectorRange_included
{
	T lower_bound, upper_bound;
	std::vector<T> m_v;
public:
	UnicVectorRange_included() :m_v(std::vector<T>{}) {};
	UnicVectorRange_included(const std::initializer_list<T>& il);
	void push_2unic(const std::initializer_list<T>& il);
	void delete_2unic(const std::initializer_list<T>& il);
	void set_range(const T& down, const T& up);
	void sort(Compare cmp_func);
};

template<typename T, typename Compare = std::less>
inline UnicVectorRange_included<T, Compare>::UnicVectorRange_included(const std::initializer_list<T>& il)
{
	this->push_2unic(il);
}

template<typename T, typename Compare = std::less>
inline void UnicVectorRange_included<T, Compare>::push_2unic(const std::initializer_list<T>& il)
{
	for (auto& i : il)
	{
		if (i >= lower_bound && i <= upper_bound)
		{
			bool unic = true;
			for (auto& v : m_v)
				if (v == i)
				{
					unic = false;
					break;
				}
			if (unic)
				back_inserter(m_v) = i;
		}
	}
}

template<typename T, typename Compare = std::less>
inline void UnicVectorRange_included<T, Compare>::delete_2unic(const std::initializer_list<T>& il)
{
	for (auto& i : il)
	{
		if (i >= lower_bound && i <= upper_bound)
		{
			for (auto& j=m_v.begin();j!=m_v.end();++j)
				if (*j == i)
				{
					j = m_v.erase(j);
					break;
				}
		}
	}
}

template<typename T, typename Compare = std::less>
inline void UnicVectorRange_included<T,Compare>::set_range(const T& down, const T& up)
{
	if (down > up) 
	{
		lower_bound = up;
		upper_bound = down;
	}
	else
	{
		lower_bound = down;
		upper_bound = up;
	}
	for (auto& j = m_v.begin(); j != m_v.end(); ++j)
		if (*j > upper_bound || *j < lower_bound)
			j = m_v.erase(j);
}
