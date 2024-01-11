#pragma once
#include<iostream>
 
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

inline void absSort(auto container)
{
	std::sort(begin(container),end(container), [](auto x) {abs(x); });
}