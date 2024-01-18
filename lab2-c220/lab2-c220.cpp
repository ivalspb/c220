#include "unic_vector_range_included.h"
#include "unic_vector_range_inherit.h"
#include <iostream>
#include <iterator>

int main(int argc, char** argv)
{
	std::cout << "init unic vector<int> at [0,3]:\n";
	UnicVectorRange_included<int> vi1({ 3,2,4,-3,1,3 }, 0, 3);
	std::copy(vi1.begin(), vi1.end(), std::ostream_iterator<int>(std::cout, ", "));
	vi1.sort();
	vi1.set_range(-3, +3);
	vi1.push_2unic({ 0,-2,4,-1,2 });
	std::cout << "\nsort + set_range [-3,3] + push vector:\n";
	std::copy(vi1.begin(), vi1.end(), std::ostream_iterator<int>(std::cout, ", "));

	std::cout << "\n--------------------------------\n";
	std::cout << "init unic vector <const char*> at [ab,bc]\n";
	UnicVectorRange_included < const char*, charcmp> vc1({ "aaa","abc","def","back","bcd","aba" }, "ab", "bc");
	std::copy(vc1.begin(), vc1.end(), std::ostream_iterator<int>(std::cout, ", "));
	vc1.sort();
	vc1.set_range("aa", "ba");
	std::cout << "\nsort + set_range [aa,ba]:\n";
	std::copy(vi1.begin(), vi1.end(), std::ostream_iterator<int>(std::cout, ", "));

	return 0;
}