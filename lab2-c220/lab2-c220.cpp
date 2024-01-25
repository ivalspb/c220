#include "unic_vector_range_included.h"
#include "unic_vector_range_inherit.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include "myString.h"
#include "MyUniquePTR.h"

int main(int argc, char** argv)
{
	{
		std::cout << "init unic vector<int> at [0,3]:\n";
		UnicVectorRange_included<int> vi1({ 3,2,4,-3,1,3 }, 0, 3);
		std::copy(vi1.begin(), vi1.end(), std::ostream_iterator<int>(std::cout, ", "));
		//vi1.sort(std::greater<>());
		vi1.sort();	

		vi1.set_range(-3, +3);
		vi1.push_2unic({ 0,-2,4,-1,2 });
		std::cout << "\nsort + set_range [-3,3] + push vector:\n";
		std::copy(vi1.begin(), vi1.end(), std::ostream_iterator<int>(std::cout, ", "));

		std::cout << "\n--------------------------------\n";
		std::cout << "init unic vector <const char*> at [ab,bc]\n";
		UnicVectorRange_included < const char*, charcmp> vc1({ "aaa","abc","def","back","bcd","aba" }, "ab", "bc", charcmp());
		std::copy(vc1.begin(), vc1.end(), std::ostream_iterator<const char*>(std::cout, ", "));
		vc1.sort(charcmp());
		vc1.set_range("aa", "ba", charcmp());
		std::cout << "\nsort + set_range [aa,ba]:\n";
		std::copy(vc1.begin(), vc1.end(), std::ostream_iterator<const char*>(std::cout, ", "));

		std::cout << "\n--------------------------------\n";
		std::cout << "init unic vector <string> at [ab,bc]\n";
		UnicVectorRange_included < std::string> vs1({ "aaa","abc","def","back","bcd","aba" }, "ab", "bc");
		std::copy(vs1.begin(), vs1.end(), std::ostream_iterator<std::string>(std::cout, ", "));
		vs1.sort();
		vs1.set_range("aa", "ba");
		std::cout << "\nsort + set_range [aa,ba]:\n";
		std::copy(vs1.begin(), vs1.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	}

	{
		std::cout << "\n--------------------------------\n";
		std::cout << "\n--------------------------------\n";
		std::cout << "\n--------------------------------\n";

		std::cout << "init unic vector<int> at [0,3]:\n";
		UnicVectorRange_inherit<int> vi2({ 3,2,4,-3,1,3 }, 0, 3);
		std::copy(vi2.begin(), vi2.end(), std::ostream_iterator<int>(std::cout, ", "));
		vi2.sort();
		vi2.set_range(-3, +3);
		vi2.push_2unic({ 0,-2,4,-1,2 });
		std::cout << "\nsort + set_range [-3,3] + push vector:\n";
		std::copy(vi2.begin(), vi2.end(), std::ostream_iterator<int>(std::cout, ", "));

		std::cout << "\n--------------------------------\n";
		std::cout << "init unic vector <const char*> at [ab,bc]\n";
		UnicVectorRange_inherit < const char*, charcmp> vc2({ "aaa","abc","def","back","bcd","aba" }, "ab", "bc", charcmp());
		std::copy(vc2.begin(), vc2.end(), std::ostream_iterator<const char*>(std::cout, ", "));
		vc2.sort(charcmp());
		vc2.set_range("aa", "ba", charcmp());
		std::cout << "\nsort + set_range [aa,ba]:\n";
		std::copy(vc2.begin(), vc2.end(), std::ostream_iterator<const char*>(std::cout, ", "));

		std::cout << "\n--------------------------------\n";
		std::cout << "init unic vector <string> at [ab,bc]\n";
		UnicVectorRange_inherit < std::string> vs2({ "aaa","abc","def","back","bcd","aba" }, "ab", "bc");
		std::copy(vs2.begin(), vs2.end(), std::ostream_iterator<std::string>(std::cout, ", "));
		vs2.sort();
		vs2.set_range("aa", "ba");
		std::cout << "\nsort + set_range [aa,ba]:\n";
		std::copy(vs2.begin(), vs2.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	}

	std::cout << "\n--------------------------------\n";
	std::cout << "\n--------------------------------\n";
	std::cout << "\n--------------------------------\n";

	{
		MyUniquePTR<MyString> p1(new MyString("abc"));
		std::cout << p1->GetString();
		p1->SetNewString("qwerty");
		MyString  s2 = *p1;
		//MyUniquePTR< MyString > p2=p1; //здесь компилятор должен выдавать ошибку => Исправьте!
		if (p1) { std::cout << "\nNo object!"; } //а это должно работать
		MyUniquePTR< MyString > p3(new MyString("vvv"));
		//p3 = p2; //и здесь компилятор должен выдавать ошибку
		vector< MyUniquePTR< MyString >> v;
		v.push_back(std::move(new MyString("1a1")));
		v.push_back(std::move(new MyString("2b2"))); //как проинициализировать??? никак)
		list< MyUniquePTR< MyString >> l;
		std::copy(std::make_move_iterator(v.begin()), std::make_move_iterator(v.end()),std::inserter(l,l.begin()));
		//как скопировать из v в l ???
		
	}


	return 0;
}