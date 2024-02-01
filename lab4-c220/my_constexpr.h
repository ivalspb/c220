#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <type_traits>


constexpr int factr_cnstexpr(int t)
{
	return t > 0 ? t * factr_cnstexpr(t - 1) : 1;
}


constexpr int get_lenght_chars(const char* bin_char)
{
	return (*(bin_char + 1) == 0) ? 1 : get_lenght_chars(bin_char + 1) + 1;
}

constexpr int pow_of_2_const(int p)
{
	return
		(p == 0) ? 1 : 2 * pow_of_2_const(p - 1);
}

constexpr  int operator""_b(const char* bn_chrs)
{
	return
		(*(bn_chrs + 1) == 0) ?//���� ����� ������?
		(*bn_chrs == '1' ? 1 : 0) ://�� ��� ������ ������� ���, ������������ �������� � ����������
		(*(bn_chrs)-'0')//���� ����� ������� ���..
		* pow_of_2_const(get_lenght_chars(bn_chrs) - 1) //..���������� �� ������� ������ ������� ���� 
		+ operator""_b(bn_chrs + 1);//� ����� ���������� ��������� ���
}

std::string operator""_toBinStr(unsigned long long digit);

template <typename T>
void printContainer(T& t)
{
	std::cout << std::endl;
	if constexpr (std::is_pointer_v<std::remove_reference_t<decltype(*(std::begin(t)))>>)
		for (auto i=std::begin(t);i!=std::end(t);++i) 
			std::cout << **i << " ";
	else
		for (auto i = std::begin(t); i != std::end(t); ++i)
			std::cout << *i << " ";
}

template <typename T, typename U>
auto my_sum(const T& t, const U& u)
{
	if constexpr (std::is_same_v < std::vector<T>, U>)//U=vector<T>
	{
		U res = u;
		for (auto& i : res) i = i + t;
		return res;
	}
	else
	{
		if constexpr (std::is_same_v < std::vector<U>, T>)//T=vector<U>
		{
			T res = t;
			for (auto& i : res) i = i + u;
			return res;
		}
		else
		{
			decltype(t+u) res = t + u;
			return res;
		}
	}
}