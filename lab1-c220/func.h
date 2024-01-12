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

string& operator-(string& s);

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

//template <>
//void NegateAll(list<string>& t)
//{
//	for (auto &s : t)
//		for (auto& c : s)
//		{
//			if (isupper(c)) c = tolower(c);
//			else c = toupper(c);
//		}
//}

inline void absSort(auto &container)
{
	std::ranges::sort(container, [](auto x, auto y) {return abs(x)<abs(y); });
}

template <typename Container1, typename Container2>
auto SumCont(Container1& container1, Container2& container2)
{
	size_t res_size = max(size(container1), size(container2));
	decltype(*begin(container1) + *begin(container2)) y{};
	vector<double>	v_res;
	v_res.resize(res_size);
	copy(begin(container2), end(container2), v_res.begin());
	transform(begin(container1), end(container1), v_res.begin(), v_res.begin(), [](auto c1, auto r) {return  c1+ r; });
	return y;
}

//template<typename Source, 
//			template <typename Source::value_type> typename Container1, 
//			template <typename Source::value_type> typename Container2, typename UnaryOperation>
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

