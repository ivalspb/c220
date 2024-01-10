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

template <typename Container, typename T= typename Container::value_type>
void NegateAll(Container& t)
{
	for (auto i : t)
		i = -i;
}

template <typename Container>
void NegateAll<string>(Container& t)
{
	for (auto s:t)
		for (auto c : s)
		{
			if (isupper(c)) c = tolower(c);
			else c = toupper(c);
		}
}