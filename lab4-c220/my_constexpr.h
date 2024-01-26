#pragma once

constexpr int factr_cnstexpr(int t)
{
	return t > 0 ? t * factr_cnstexpr(t - 1) : 1;
}


constexpr int operator""_b(const char* bin_char)
{
	int x = 0;
	return x=
		(*(bin_char+1 ) == 0) 
		? 
		*bin_char=='1'? 1:0
		:
		2 * (static_cast<int>(*(bin_char)) - 48) + operator"" _b(bin_char + 1);
}
