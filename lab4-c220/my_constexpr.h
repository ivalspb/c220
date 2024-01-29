#pragma once
//#include <iostream>
#include <cstdint>
#include <string>

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