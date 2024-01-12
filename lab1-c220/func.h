#pragma once
#include<iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

inline void PrintAnyCont(auto &Container)
{
	cout << endl;
	for (const auto& i : Container)
		cout << i << ", ";
	cout << endl;
}

string& operator-(string& s);

template <typename Container>
void NegateAll(Container& t)
{
	for (auto &i : t)
		i = -i;
}

inline void absSort(auto &container)
{
	std::sort(begin(container),end(container), [](auto x, auto y) {return abs(x) < abs(y); });
}

template <typename Container1, typename Container2>
auto SumCont(Container1& container1, Container2& container2)
{//надо ли проверять что контейнеры оба не пустые????
	vector<decltype(*begin(container1) + *begin(container2))>	v_res(max(size(container1), size(container2)));
	copy(begin(container2), end(container2), v_res.begin());
	transform(begin(container1), end(container1), v_res.begin(), v_res.begin(), [](auto c1, auto r) {return  c1+ r; });
	return v_res;
}

template<typename Source,typename Container1, typename Container2, typename UnaryOperation>
void Separate(Source& source, Container1& container1, Container2& container2, UnaryOperation condition)
{
	auto s = begin(source);
	auto se = end(source);
	for (; s != se; ++s)
	{
		if (condition(*s)) 
			copy(s, s+1, inserter(container1, container1.begin()));
		else 
			copy(s, s+1, inserter(container2, container2.begin()));
	}
}

