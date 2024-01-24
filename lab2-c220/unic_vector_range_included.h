#pragma once
#include <vector>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <functional>

template <typename T, typename Compare=std::less<> >
class UnicVectorRange_included
{
	T lower_bound{}, upper_bound{};
	std::vector<T> m_v;
public:
	UnicVectorRange_included()=default;
	UnicVectorRange_included(const std::initializer_list<T>& il, const T&lo, const T& hi,  Compare cmp_func=std::less<>());
	UnicVectorRange_included(const typename UnicVectorRange_included& other)=default;
	UnicVectorRange_included(typename UnicVectorRange_included&& tmp_other) = default;
	~UnicVectorRange_included() = default;
	UnicVectorRange_included& operator=(const typename UnicVectorRange_included& other) = default;
	UnicVectorRange_included& operator=(typename UnicVectorRange_included&& tmp_other) = default;
	void push_2unic(const std::initializer_list<T>& il,  Compare cmp_func = std::less<>());
	void pop_2unic(const std::initializer_list<T>& il,   Compare cmp_func = std::less<>());
	void set_range(const T& down, const T& up,  Compare cmp_func = std::less<>());
	template <typename Pred=std::less<> > void sort(Pred cmp_func = std::less<>());
	auto begin() { return m_v.begin(); }
	auto end() { return m_v.end(); }
};

template<typename T, typename Compare>
inline UnicVectorRange_included<T, Compare>::UnicVectorRange_included(const std::initializer_list<T>& il, const T& lo, const T& hi,  Compare cmp_func)
{
	lower_bound = lo;
	upper_bound = hi;
	this->push_2unic(il,cmp_func);
}

template<typename T, typename Compare>
inline void UnicVectorRange_included<T, Compare>::push_2unic(const std::initializer_list<T>& il,  Compare cmp_func)
{
	for (auto& i : il)
		if (!cmp_func(i, lower_bound) && !cmp_func(upper_bound, i) && (std::find(m_v.begin(), m_v.end(), i) == m_v.end()))
			m_v.push_back(i);
}

template<typename T, typename Compare>
inline void UnicVectorRange_included<T, Compare>::pop_2unic(const std::initializer_list<T>& il,  Compare cmp_func)
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
inline void UnicVectorRange_included<T,Compare>::set_range(const T& down, const T& up,  Compare cmp_func)
{
	if (cmp_func(up,down)) 
	{
		lower_bound = up;
		upper_bound = down;
	}
	else
	{
		lower_bound = down;
		upper_bound = up;
	}
	for (auto j = m_v.begin(); j != m_v.end(); ++j)
		if (cmp_func(upper_bound, *j)  || cmp_func(*j, lower_bound))
		{
			j = m_v.erase(j);
			if(j == m_v.end()) break;
		}
}

template<typename T, typename Compare>
template <typename Pred>
inline void UnicVectorRange_included<T, Compare>::sort( Pred cmp_func)
{
	std::sort(m_v.begin(), m_v.end(), cmp_func);
}

struct charcmp {
	bool operator()(const char* s1, const char* s2) const { return strcmp(s1, s2) < 0; }
};