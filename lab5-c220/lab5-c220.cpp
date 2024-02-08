#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <string>
#include "deleters.h"


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
			std::vector<std::unique_ptr<std::string*>> v;
			v.push_back(std::make_unique<std::string*>(new std::string("aa")));
			v.push_back(std::make_unique<std::string*>(new std::string("bb")));
			v.push_back(std::make_unique<std::string*>(new std::string("cc")));

			//������������ ��� ������
			std::cout << std::endl;
			for (const auto& i : v)
				std::cout << **i << " ";
			__asm nop
			//??? ����������� ����������� ��������� ��������?
		} //???

		{//1.c - ��������� ������� 1.b �������� ����������� �������� ���������� ������
		 //��������� ������� (��������, �������� ��������� �������: "AAA" -> "AAA_1")  
			std::vector<std::unique_ptr<std::string*>> v;
			v.push_back(std::make_unique<std::string*>(new std::string("aa")));
			v.push_back(std::make_unique<std::string*>(new std::string("bb")));
			v.push_back(std::make_unique<std::string*>(new std::string("cc")));

			std::cout << std::endl;
			for (auto& i : v) 
			{
				**i += "_1";
				std::cout << **i << " ";
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

			typedef  std::unique_ptr<std::string*> u_p_str_t;
			std::vector<u_p_str_t>v_u_p_str;
			v_u_p_str.push_back(std::make_unique<std::string*>(new std::string("v_u_p_str_aaa")));
			v_u_p_str.push_back(std::make_unique<std::string*>(new std::string("v_u_p_str_bbb")));
			v_u_p_str.push_back(std::make_unique<std::string*>(new std::string("v_u_p_str_ccc")));
			
			std::cout << "\n\nThe vector of unique_ptr to string*\n";
			for (const auto& i : v_u_p_str)
				std::cout << **i << " ";

			//����������� ��������� copy() ���������� �������� ������� � ������ ������ � ���������� 
			//���� �� ����
			//���������: ������������ ��������� � ������ std::make_move_iterator
			std::list< u_p_str_t>l_u_p_str;
			std::copy(std::make_move_iterator(v_u_p_str.begin()), std::make_move_iterator(v_u_p_str.end()), std::inserter(l_u_p_str, l_u_p_str.begin()));

			std::cout << "\n\nThe list of unique_ptr to string*\n";
			for (const auto& i : l_u_p_str)
				std::cout << **i << " ";

			__asm nop

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
	size_t number_of_writers = rand() % 10;
	auto writers = std::unique_ptr<writer_t[], UniqCountDeleter<writer_t>>(new writer_t[number_of_writers], UniqCountDeleter<writer_t>(number_of_writers));
	//(new std::ofstream(fn), FileDeleter(fn));
	

	//�������� ����� �������� ��������� ������� ��������� ������ �� "���������" �������� � ����
	//���� �������


	__asm nop
	}//�������� �����???

	
	/***************************************************************/
	//������� 3.
	{
		//��� ������ ��������� ���� string
		std::string strings[] = { "abc", "123", "qwerty", "#$%" };
		//�� ���������� ��������� ������ ������ ������������ � ������������ ����������.
		//��������� ���������� ��������������� �������� �) ��� ����������� � �) ��� ��������� �������
		//��������� � �������!

		//� std::set "����������" �� �������� ������� ��� �����, ������� �������� ������ ����� 


		__asm nop
		/******************************************************************************************/

		//� std::vector "����������" ������� ��� �����, ������� �������� ������ ����� 
		//������� �� �����
		//������� �����

		//std::vector<std::shared_ptr < std::string>>

		/******************************************************************************************/
		//���� "����������" ������� ��� �����, ������� �� �������� �� �������� ����, �� �������� ����
		//� ������ �������


	}


	/******************************************************************************************/
	//������� 4. 
	{
		//����:
		std::string ar[] = { "my","Hello", "World" };
		std::vector < std::shared_ptr<std::string>> v = { std::make_shared<std::string>("good"), std::make_shared<std::string>("bye") };



		//�) ��������� �������� � ������ ������� ��� ��������� �������, �� ������� �������� �������! 
		//�) ������������� ������ �� �������� � ������� �� �����
		//�) ���������� ���������� ������������ ������


		__asm nop
	}
	/***************************************************************/
		//������� 5. shared_ptr � weak_ptr
		//������� ��������������� ������ ����������� ������ human. � ������ ��������:
		//��� - string
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