#include "my_constexpr.h"

std::string operator""_toBinStr(unsigned long long digit)
{
    std::string res="0b";
    if (digit < 2) res += std::to_string(digit);
    else
    {
        res =  operator""_toBinStr(digit / 2)+ std::to_string(digit % 2);
    }
    return res;
}
