#pragma once
#include <vector>
#include <initializer_list>
#include <iterator>
#include <algorithm>

template <typename T, typename Compare = std::less<T> >
class UnicVectorRange_inherit :private std::vector<T>
{
	T lower_bound, upper_bound;
	typedef std::vector<T> vector;
public:
	UnicVectorRange_inherit() = default;
	UnicVectorRange_inherit(const std::initializer_list<T>& il, const T& lo, const T& hi, const Compare& cmp_fn = std::less<T>());
	UnicVectorRange_inherit(const typename UnicVectorRange_inherit& other) = default;
	UnicVectorRange_inherit(typename UnicVectorRange_inherit&& tmp_other) = default;
	~UnicVectorRange_inherit() = default;
	UnicVectorRange_inherit& operator=(const typename UnicVectorRange_inherit& other) = default;
	UnicVectorRange_inherit& operator=(typename UnicVectorRange_inherit&& tmp_other) = default;
	void push_2unic(const std::initializer_list<T>& il, const Compare& cmp_func = std::less<T>());
	void pop_2unic(const std::initializer_list<T>& il, const Compare& cmp_func = std::less<T>());
	void set_range(const T& down, const T& up, const Compare& cmp_func = std::less<T>());
	void sort(const Compare& cmp_func = std::less<T>());
	auto begin() { return vector::begin(); }//это считается полиморфизмом? Не возникает проблем с не виртуальным деструктором вектора?
	auto end() { return vector::end(); }
};

template<typename T, typename Compare>
inline UnicVectorRange_inherit<T, Compare>::UnicVectorRange_inherit(const std::initializer_list<T>& il, const T& lo, const T& hi, const Compare& cmp_func)
{
	lower_bound = lo;
	upper_bound = hi;
	push_2unic(il, cmp_func);
}

template<typename T, typename Compare>
inline void UnicVectorRange_inherit<T, Compare>::push_2unic(const std::initializer_list<T>& il, const Compare& cmp_func)
{
	for (auto& i : il)
		if (!cmp_func(i, lower_bound) && !cmp_func(upper_bound, i) && (std::find(begin(), end(), i) == end()))
		vector::push_back(i);
}

template<typename T, typename Compare>
inline void UnicVectorRange_inherit<T, Compare>::pop_2unic(const std::initializer_list<T>& il, const Compare& cmp_func)
{
	for (auto& i : il)
	{
		if (!cmp_func(i, lower_bound) && !cmp_func(upper_bound, i))
		{
			for (auto& j = begin(); j != end(); ++j)
				if (*j == i)
				{
					j = vector::erase(j);
					break;
				}
		}
	}
}

template<typename T, typename Compare>
inline void UnicVectorRange_inherit<T, Compare>::set_range(const T& down, const T& up, const Compare& cmp_func)
{
	if (cmp_func(up, down))
	{
		lower_bound = up;
		upper_bound = down;
	}
	else
	{
		lower_bound = down;
		upper_bound = up;
	}
	for (auto j = begin(); j != end(); ++j)
		if (cmp_func(upper_bound, *j) || cmp_func(*j, lower_bound))
		{
			j = vector::erase(j);
			if (j == end()) break;
		}
}

template<typename T, typename Compare>
inline void UnicVectorRange_inherit<T, Compare>::sort(const Compare& cmp_func)
{
	std::sort(begin(), end(), cmp_func);
}
