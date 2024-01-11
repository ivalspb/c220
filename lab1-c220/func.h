#pragma once
#include<iostream>
#include <algorithm>
 
using namespace std;

inline void PrintAnyCont(auto &Container)
{
	cout << endl;
	for (const auto& i : Container)
		cout << i << ", ";
	cout << endl;
}

template <typename Container>
void NegateAll(Container& t)
{
	for (auto &i : t)
		i = -i;
}

//template <typename Container<string>>
//void NegateAll(Container& t)
//{
//	for (auto &s:t)
//		for (auto& c : s)
//		{
//			if (isupper(c)) c = tolower(c);
//			else c = toupper(c);
//		}
//}

template <>
void NegateAll(list<string>& t)
{
	for (auto &s : t)
		for (auto& c : s)
		{
			if (isupper(c)) c = tolower(c);
			else c = toupper(c);
		}
}

inline void absSort(auto &container)
{
	std::ranges::sort(container, [](auto x, auto y) {return abs(x)<abs(y); });
}

template <typename Container1, typename Container2, 
	typename T1 = typename Container1::value_type, typename T2 = typename Container2::value_type,
	typename T=typename common_type<T1,T2>>
typename vector<T>& SumCont(Container1& container1, Container2& container2)
{
	size_t res_size = max(size(container1), size(container2));
	vector<T> v_res(res_size);
	copy(begin(container2), end(container2), v_res.begin());
	transform(begin(container1), end(container1), v_res.begin(), [](auto c1, auto r) {return  c1 + r; });
	return v_res;
}