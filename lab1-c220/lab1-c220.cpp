//�������� 1:
// enum class
// initializer_list � ������������� ������ �������������
// auto
// decltype
// lambda 
// template variable
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <deque>
#include "func.h"

int main()
{
	using namespace std;
	//������� 1. 
	{
		enum class months:unsigned char { January, February, March/*...*/ };
		enum class weekDays :unsigned char{ Monday, Tuesday /*...*/ };
		using enum months;

		months m = January;
		//�) ������� �������� (��� ������, ��� ���������� ��
		//������ ��������� ������������ ������������ �������
		//���������!)

		//if (m == weekDays::Monday) { /*...*/ }

		//�) ������������� ������������� ������
		months year[] = { January, February, March };
		size_t n = sizeof(year); //???

		__asm nop
	}


	/**********************************************************/
		//������� 2. �������� � � ������� ������ �������������
		//��������� ���������� ������ � ���������� - string
		//� ������� range-based for ������������ ��� ����� � 	
		//������� ������� � ��������� ������� ������ ��������
		//�����������
	{

		vector<string>vs = { "Aa+1a","B2*bb","Cc3&c" };
		for (auto &s : vs)
			for (auto& c : s) 
				c = toupper(c);
		__asm nop
	}


	/**********************************************************/
		///������� 3. �������� � ��������� ����������
		//map ����� ��������� (3� � 3�) ����� �������, ����� �� �������� 
		//� �������� ����� �����, � � �������� �������� 
		//��������������� �� �������� ������������ ���� (string), 
		//������������ � ���� �����

		//3�. ������������������ map "�������" ����������� ������ �������������
		//� ������� range-based for � structured binding
		//������������ ����������, ��������: A: any, apple, away
	{

		map<char, set<string>> dict = { {'b',{"bBb","bvb","bbb"}},{'A',{"Aaa","Aza","Abc"}} };

		for (const auto& [ch, words] : dict)
		{
			cout <<endl<< ch << ": ";
			for (const auto& word : words)
				cout << word << ", ";
		};
		__asm nop
	}

	//3�. �������� ������ map � ����������� �������� ������
	//��� ���������� �������.
	//� ������� range-based for � structured binding
	//������������ ����������, ��������: A: any, apple, away
	{
		//���� (��������):
		const char* s[] = { "yong", "away", "bar", "any", "son", "apple" };
		map<char, set<string>> dict;
		for (const auto& word : s) 
			dict[word[0]].insert({word});//init string by const char* and insert it to the set

		for (const auto& [ch, words] : dict)
		{
			cout << endl << ch << ": ";
			for (const auto& word : words)
				cout << word << ", ";
		};
		__asm nop
	}


	/*********************************************************/
		//������� 4. ������� ������� ��� ������ �� ������
		//��������� �������������������, �������� ����:
	{
		vector<double> vd = { 1.1,2.2,3.3 };
		PrintAnyCont(vd);

		string s("abc");
		PrintAnyCont(s);

		int ar[] = { 1, 2, 3 };
		PrintAnyCont(ar);

		initializer_list<int> il{ 3,4,5 };
		PrintAnyCont(il);		

		__asm nop
	}


	/********************************************************/
		///������� 5. 	
		//C������ ������� ��� "���������" ��������, ��������:
		//����: {1, -2, 5}, �����: {-1, 2, -5})
		//��������� �������� ���� std::string ����� ��������� "aBc1" -> "AbC1"
		//��������� �������������������, �������� ����:
	{
		vector<double> vd{ 1.1,2.2,3.3 };
		NegateAll(vd);

		list<string> ls{ "aBc", "Qwerty", "n12" };
		NegateAll(ls);

		int ar[]{ 1, 2, 3 };
		NegateAll(ar);

		__asm nop

	}


	/********************************************************/
		//������� 6. ����������� ������� ���������� �� ������
		//��������� �������������������, �������� ����
		//���������� ��� ���������� ����� ������������ ����������
		//�������� sort(), � ��� ������� ������� - ������-�������
	{
		vector<double> vd = { -3.3,  2.2, -1.1 };
		//absSort(vd);


		int ar[] = { -3, 2, -1 };
		//absSort(ar);

		__asm nop
	}


	/********************************************************/
		//������� 7.
		//�������� �������, ������� ����� ����������� �
		//���������� ������, ������ ������� 
		//�������� �������� ������ ��������� ���� 
		//������������������� ������ �����
		//� � ���������� ������� ����.

		//��������� 1: ��� ��� ������������������ ����� ����
		//������ �����, ������� ������� ������ ���������������
		//������� ������������ �� ����

		//��������� 2: ��������� � ����������� �������������
		//���������� copy() � transform(), � ������� 
		//���������������� �������� ������ � ���� �������
		//�������� ������-��������

		//��������:
	{
		vector<int> v{ 1,2,3,4 };
		list<double> l{ 1.1, 2.2, 3.3, 4.4, 5.5 };

		//??? = SumCont(v, l);


		list<int> ll{ 1, 2, 3, 4, 5, 6, 7, 8 };
		double ar[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
		//??? = SumCont(ar, ll);


		set<std::string> s{ "abc", "qwerty", "my" };
		deque<const char*> d{ "111", "22" };
		//??? = SumCont(s, d);

		__asm nop
	}


	/********************************************************/
		//������� 8. ���������� �������, ������� ��������� ��������� ���������:	
		//�������������� ������������������ ������ ���� � ���������� ������ ����, 
		//��� (������) ���������� ������ ���� �� vector, list, deque, set 
		//� ���������� ���� �� ����, ��� � � �������������� ������������������ 

		//������� ������ "���������" �������� �������� ������������������ � ��� ������ ���������� 
		//�������� ��������� �������. ������� ������ ������-��������
		//�������� ������������������ ��� ���� �� ��������
	{
		//�������� 1:
		std::vector<int> v{ 1,2,3,4,5 };
		std::list<int> l; //���� ������
		std::deque<int> d; //� ���� ��������
		//Separate(v, l, d, <�������>);

		__asm nop
	}
	{
		//2.
		//��������� �������� �������: �� ��������, ������� �������� � �������� ��������, � ���� //���������, ��������� - � ������
		double ar[] = { 0.8, 1.1, 33.3, -4.1, 5.5 };
		std::set<double> s; //���� ��, ������� �������� � [0,6]
		std::vector<double> v; //���� ���������
	}


	/********************************************************/
		//������� 9. C ������� ��������� for_each()!!! 
		//(� �� count_if()) ��������� ������� ���� � �������
		//��������.
		//  ������������ ������ �������
	{
		char s[] = "Hello World!";
		//for_each


		__asm nop
	}


	/********************************************************/
		//������� 10. ����������� ����������� enum � ��������� �������������  - enumToString
		// � �������� - stringToEnum

		//���������: 
		//***********
		//1. ��������������� ����������� ���������� ������ ��� ����� ����� ���-�� ������� =>
		//1.1 ����������� ��������� � ������������ ������ ���� ����������� => ��������������� ������
		//���� ������ ���� �����������, => ���������� ������ ����� ���� ������������ � ��������
		//����� � std::map

		//1.2 � ��� �������� (��������������� ���������� ����������)
		//����� ���� ������ � ���� ����� ����������� (�������� ������, ������, ��� �������� �� �����������) 
		//=> �������� ��������� std::map<string,<��������> >

		//1.3 �������� ��������� �++11 ���������� ������������� ���� ����� ���� ������� ������� � ����,
		//� �������� �� ���������� ������������� ����������� 

		//***********
		//2.1 ��� ��� ���� ������������ ������, �� enumToString � stringToEnum ������ ���� ����������
		//2.2 ������������ ����� ��������� ��� ������������ �������� � ������� ��������, �������
		//   ������ �� ������������� => ������!


		//***********
		//3. ����� �������� � map<string, <��������> > �� �������� �� ���� ������������, ��������� ��� ��������������
		//��������� ���������� (� ��������� ��������� � ����������� ������������� ��������� ����������)


		//***********

	{
		//��������:
	/*
			COLORS c1;
			try {
				c1 = stringToEnum<COLORS>("blue");
			}
			catch (...)
			{
			//...
			}


			auto Str = enumToString(c1);
	*/

		__asm nop
	}

	return 0;
}
