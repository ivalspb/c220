#include "func.h"

string& operator-(string& s)
{
	for (auto& c : s)
	{
		if (isupper(c)) c = tolower(c);
		else c = toupper(c);
	}
	return s;
}
