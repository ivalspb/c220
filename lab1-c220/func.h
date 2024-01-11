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

template <typename Container1, typename Container2>
auto SumCont(Container1& container1, Container2& container2)
{
	vector<common_type_t<remove_reference_t<decltype(*begin(declval<Container1&>()))>, 
							remove_reference_t<decltype(*begin(declval<Container2&>()))>>>
								v_res(max(size(container1), size(container2)));
	copy(begin(container2), end(container2), v_res.begin());
	transform(begin(container1), end(container1), v_res.begin(), v_res.begin(), [](auto c1, auto r) {return  c1+ r; });
	return v_res;
}