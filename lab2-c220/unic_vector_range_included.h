#pragma once
#include <vector>
#include <initializer_list>
#include <iterator>

template <typename T, typename Compare=std::less<T> >
class UnicVectorRange_included
{
	T lower_bound, upper_bound;
	std::vector<T> m_v;
public:
	UnicVectorRange_included() :m_v(std::vector<T>{}) {};
	UnicVectorRange_included(const std::initializer_list<T>& il, const Compare &cmp_func);
	UnicVectorRange_included(const typename UnicVectorRange_included& other)=default;
	UnicVectorRange_included(typename UnicVectorRange_included&& tmp_other) = default;
	UnicVectorRange_included& operator=(const typename UnicVectorRange_included& other) = default;
	UnicVectorRange_included& operator=(typename UnicVectorRange_included&& tmp_other) = default;
	void push_2unic(const std::initializer_list<T>& il, const Compare& cmp_func);
	void delete_2unic(const std::initializer_list<T>& il, const Compare& cmp_func);
	void set_range(const T& down, const T& up, const Compare& cmp_func);
	void sort(const Compare &cmp_func);
	typedef T* iterator;
	iterator begin() { return m_v.begin() };
	iterator end() { return m_v.end() };
};

template<typename T, typename Compare>
inline UnicVectorRange_included<T, Compare>::UnicVectorRange_included(const std::initializer_list<T>& il, const Compare& cmp_func)
{
	this->push_2unic(il,cmp_func);
}

template<typename T, typename Compare>
inline void UnicVectorRange_included<T, Compare>::push_2unic(const std::initializer_list<T>& il, const Compare& cmp_func)
{
	for (auto& i : il)
		if (!cmp_func(i, lower_bound) && !cmp_func(upper_bound, i) && (std::find(m_v.begin(), m_v.end(), i) == m_v.end()))
			m_v.push_back(i);
}

template<typename T, typename Compare>
inline void UnicVectorRange_included<T, Compare>::delete_2unic(const std::initializer_list<T>& il, const Compare& cmp_func)
{
	for (auto& i : il)
	{
		if (!cmp_func(i, lower_bound) && !cmp_func(upper_bound, i))
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

template<typename T, typename Compare>
inline void UnicVectorRange_included<T,Compare>::set_range(const T& down, const T& up, const Compare& cmp_func)
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
		if (cmp_func(upper_bound, *j)  || cmp_func(*j, lower_bound))
			j = m_v.erase(j);
}

template<typename T, typename Compare>
inline void UnicVectorRange_included<T, Compare>::sort(const Compare &cmp_func)
{
	std::sort(m_v.begin(), m_v.end(), cmp_func);
}

