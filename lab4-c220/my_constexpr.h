#pragma once
#include <iostream>

constexpr int factr_cnstexpr(int t)
{
	return t > 0 ? t * factr_cnstexpr(t - 1) : 1;
}


constexpr int reverse_bin(const char* rev_bin_char)
{
	return
		(*(rev_bin_char + 1) == 0) ? (*rev_bin_char == '1' ? 1 : 0) 
		: 
		(static_cast<int>(*(rev_bin_char)) - 48) + 2 * (reverse_bin(rev_bin_char + 1));
}

constexpr int operator""_b(const char* bin_char)
{
	return (get_lenght_chars(bin_char)==1)
}

constexpr int get_lenght_chars(const char* bin_char)
{
	return (*(bin_char + 1) == 0) ? 1 : get_lenght_chars(bin_char + 1) + 1;
}