#pragma once
#include <vector>
#include <initializer_list>
#include <iterator>

template <typename T,  T lower_bound,  T upper_bound>
class UnicVectorRange_included
{
	std::vector<T> m_v;
public:
	UnicVectorRange_included() :m_v(std::vector<T>{}) {};
	UnicVectorRange_included(const std::initializer_list<T>& il);
	void push_2unic(const std::initializer_list<T>& il);
	void delete_2unic(const std::initializer_list<T>& il);
};

template<typename T,  T lower_bound,  T upper_bound>
inline UnicVectorRange_included<T,  lower_bound,  upper_bound>::UnicVectorRange_included(const std::initializer_list<T>& il)
{
	this->push_2unic(il);
}

template<typename T,  T lower_bound,  T upper_bound>
inline void UnicVectorRange_included<T, lower_bound, upper_bound>::push_2unic(const std::initializer_list<T>& il)
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

template<typename T,  T lower_bound,  T upper_bound>
inline void UnicVectorRange_included<T, lower_bound, upper_bound>::delete_2unic(const std::initializer_list<T>& il)
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
