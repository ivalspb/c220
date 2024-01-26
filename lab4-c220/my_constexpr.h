#pragma once
#include <iostream>

constexpr int factr_cnstexpr(int t)
{
	return t > 0 ? t * factr_cnstexpr(t - 1) : 1;
}


inline int operator""_b(const char* bin_char)
{
	int x = 0;
	x = (*(bin_char + 1) == 0) ? (*bin_char == '1' ? 1 : 0) : (static_cast<int>(*(bin_char)) - 48)+ 2*(operator"" _b(bin_char + 1)) ;
	 std::cout << bin_char<<" x= \n" << x;
	 return x;
}
