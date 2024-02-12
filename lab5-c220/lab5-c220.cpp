#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <string>
#include "deleters.h"
#include "Human.h"


int main()
{

	//////////////////////////////////////////////////////////////////////////////////////////////
	//������� 1. unique_ptr
	{

		//1.� - ���������� ���������� ���������� ���������
		{

			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };

			//������������ ��� ������
			for (const auto& i : v) 
				std::cout << *i << " ";
			//???
			for (auto& i : v) 
				delete i;
			__asm nop
			
		} //???

		//1.b - ������������� ������� 1.�:
		 //���������� ����������� std::unique_ptr: 
		 //����������� ���������� (��������� ��� ������ ������� ������������ std::unique_ptr), 
		 //���������� �������� ���������� �� ����������� ����������� ������� std::string, 
		 //���������������,
		 //� ������������ ��������
		 //

		{
			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::make_unique<std::string>("aa"));
			v.push_back(std::make_unique<std::string>("bb"));
			v.push_back(std::make_unique<std::string>("cc"));

			//������������ ��� ������
			std::cout << std::endl;
			for (const auto& i : v)
				std::cout << *i << " ";
			__asm nop
			//??? ����������� ����������� ��������� ��������?
		} //???

		{//1.c - ��������� ������� 1.b �������� ����������� �������� ���������� ������
		 //��������� ������� (��������, �������� ��������� �������: "AAA" -> "AAA_1")  
			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::make_unique<std::string>("aa"));
			v.push_back(std::make_unique<std::string>("bb"));
			v.push_back(std::make_unique<std::string>("cc"));

			std::cout << std::endl;
			for (auto& i : v) 
			{
				*i += "_1";
				std::cout << *i << " ";
			}


			__asm nop
		}

		{//1.d - ������������ ������ ��������	

		 //�������� unique_ptr, ������� �������� �������� ��� ������������� �������
		 //� ���������� std::string

			size_t n = 10;
			auto p_dyn_ar_str = std::make_unique<std::string[]>(n);

		 //� ������� unique_ptr::operator[] ��������� ��������� ������ ����������
		 
			std::cout << std::endl;
			for (size_t i = 0; i < n; i++)
			{
				p_dyn_ar_str[i] = "Test string "+std::to_string(i)+",";
				std::cout << p_dyn_ar_str[i]<<" ";
			}
		 //����� ���������� ������������ ������?

			__asm nop
		}

		{//1.e - ������� ������������ �������� � ���������������� delete-������� (�������)
		 //����� �������� ������ ���������� �� ����������� ��������� �������
		 //�������� unique_ptr ��� ������ �������
		 //���������� ���������������� delete-������� (�������) ��� ����������� 
		 //������������ ������

			std::string* arStrPtr[] = { new std::string("aad"), new std::string("bbd"), new std::string("ccd") };
			size_t n = std::size(arStrPtr);
			auto deleter_dyn_str = [n](auto& x) {for (size_t i = 0; i < n; i++) delete x[i]; };
			std::unique_ptr<std::string*[], decltype(deleter_dyn_str)> p_arStrPtr (arStrPtr, deleter_dyn_str);
			__asm nop
		}

		{
			//1.f �������� � ��������� ������, ���������� unique_ptr ��� ���������� �� std::string
//*
			typedef  std::unique_ptr<std::string> u_p_str_t;
			std::vector<u_p_str_t>v_u_p_str;
			v_u_p_str.push_back(std::make_unique<std::string>("v_u_p_str_aaa"));
			v_u_p_str.push_back(std::make_unique<std::string>("v_u_p_str_bbb"));
			v_u_p_str.push_back(std::make_unique<std::string>("v_u_p_str_ccc"));
			
			std::cout << "\n\nThe vector of unique_ptr to string*\n";
			for (const auto& i : v_u_p_str)
				std::cout << *i << " ";

			//����������� ��������� copy() ���������� �������� ������� � ������ ������ � ���������� 
			//���� �� ����
			//���������: ������������ ��������� � ������ std::make_move_iterator
			std::list< u_p_str_t>l_u_p_str;
			std::copy(std::make_move_iterator(v_u_p_str.begin()), std::make_move_iterator(v_u_p_str.end()), std::inserter(l_u_p_str, l_u_p_str.begin()));

			std::cout << "\n\nThe list of unique_ptr to string*\n";
			for (const auto& i : l_u_p_str)
				std::cout << *i << " ";

	////*/		__asm nop

		}
		__asm nop

	}

	////////////////////////////////////////////////////////////////////////////////
	//������� 2.shared_ptr + ���������������� delete-������� 

	//����������� ����������� ������ � ���� ������ (�������) �� ������ ���������� 
	//��� ��� ��� "��������" ����� �� ������� ���������� ���� ������ � ���� � ��� �� ����,
	//������� ������������ �� ����������� ������������ ����� � ��� �� �������� ������ ������ =>
	//���������� �������� ��� ������ ��������� �������� shared_ptr
	//�. ������ �������� ������ �������/������� ���� ��� ������
	//�. ��� ��������� �������� ������ �������������� � �������������
	//�. ��������� �������� ��������� ������ ������� ����

	//���������: ����������� ������� ������ ����� � ������� ������� rand()
	
	{

	//"��������":
	//������� writer1, writer2

		std::string fn("tmpfile.txt");
		typedef std::shared_ptr<std::ofstream> writer_t;
		std::vector<writer_t> writers(rand() % 30, writer_t(new std::ofstream(fn), FileDeleter(fn)));
		//���������������� ���� �� �����������, ��� ��� ������� �� ������ � ��� � ����� ���� ������������ 
		for (size_t session_number = 0; session_number < writers.size(); session_number++)
		{
			size_t session_writer = rand() % writers.size();
			(*writers[session_writer]) << "\nWriter #" << session_writer << ":\n";
			for (size_t session_strings = 0; session_strings < rand() % 10; session_strings++)
			{
				//�������� ����� �������� ��������� ������� ��������� ������ �� "���������" �������� � ����
				//���� �������
				(*writers[session_writer]) << rand() % 100 << " ";
			}
		}

		__asm nop
	}//�������� �����???

	__asm nop

	/***************************************************************/
	//������� 3.
	{
		//��� ������ ��������� ���� string
		std::string strings[] = { "abc", "123", "qwerty", "#$%" };
		//�� ���������� ��������� ������ ������ ������������ � ������������ ����������.
		//��������� ���������� ��������������� �������� �) ��� ����������� � �) ��� ��������� �������
		//��������� � �������!

		//� std::set "����������" �� �������� ������� ��� �����, ������� �������� ������ ����� 
		std::set<std::shared_ptr<std::string>>  s_p_str;
		for (const auto& word : strings)
		{
			bool only_letters = true;
			for (const auto& c : word)
				if (c < 'a' || c>'z') 
				{
					only_letters = false;
					break;
				}
			if (only_letters) s_p_str.insert(std::make_shared<std::string>(word));
		}
		std::cout << "\nThe set:\n";
		for (const auto& i : s_p_str) std::cout << *i << " ";

		/******************************************************************************************/

		//� std::vector "����������" ������� ��� �����, ������� �������� ������ ����� 
		//������� �� �����
		//������� �����

		std::vector<std::shared_ptr < std::string>> v_p_str;
		for (const auto& word : strings)
		{
			bool only_digits = true;
			for(const auto& c:word)
				if (c < '0' || c>'9')
				{
					only_digits = false;
					break;
				}
			if (only_digits) v_p_str.push_back(std::make_shared<std::string>(word));
		}
		std::cout << "\nThe vector contains only digits:\n";
		int sum_v = 0;
		for (const auto& i : v_p_str) 
		{
			std::cout << *i << " ";
			sum_v += std::stoi(*i);
		}

		/******************************************************************************************/
		//���� "����������" ������� ��� �����, ������� �� �������� �� �������� ����, �� �������� ����
		//� ������ �������
		std::vector<std::shared_ptr < std::string>> v_p_str2;
		for (const auto& word : strings)
		{
			bool not_digits_not_letters = true;
			for(const auto& c:word)
				if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
				{
					not_digits_not_letters = false;
					break;
				}
			if (not_digits_not_letters) v_p_str2.push_back(std::make_shared<std::string>(word));
		}
		std::cout << "\nThe vector contains not digits, nor letters:\n";
		for (const auto& i : v_p_str2)
			std::cout << *i << " ";

		__asm nop


	}

	__asm nop

	/******************************************************************************************/
	//������� 4. 
	{
		//����:
		std::string ar[] = { "my","Hello", "World" };
		std::vector < std::shared_ptr<std::string>> v = { std::make_shared<std::string>("good"), std::make_shared<std::string>("bye") };



		//�) ��������� �������� � ������ ������� ��� ��������� �������, �� ������� �������� �������! 
		
		for (const auto& i : ar)
			v.push_back(std::make_shared<std::string>(i));
		 
		//�) ������������� ������ �� �������� � ������� �� �����
		
		std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return *a < *b; });
		std::cout << "\n4. Sorted vector:\n";
		for (const auto& i : v) std::cout << *i << " ";

		//�) ���������� ���������� ������������ ������


		__asm nop
	}
	/***************************************************************/
		//������� 5. shared_ptr � weak_ptr
		//������� ��������������� ������ ����������� ������ human. � ������ ��������:
		//��� - stringuuuu
		//�������� �������: ��� ��� ��� ���...
		//�������� - shared_ptr (�������� �� ������ ��������...)
		//���� - ��������� �� weak_ptr (����� �������� ����������� ������������)

		//������ ������ human:
		//����������� - ��� ������������� ����� � ��������
		//����������� �����������, �������� ������������, move ???
		//����������� ����� child() - 
		//				������ ������� ������� � ������� ������� ��� ����������� ��������
		//				+ ������������ ��� ����� ������� � ���������� � ��������

		//������ ����������� ����������� ��������������� ������ ��� ���������� ����������

	{
		//������� ������ � ����-�� ���������� => "����-���� ��� �� ����, ��������, ���� � ���"
		//(�� ���� �� ����� ���� ��� ���� � ��� ����):


		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//� ��� ��������� ���� - child():


		//� � ����� � ���� ������� ���� ����:


		//...
		__asm nop
	}





	__asm nop

}