#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include <string>


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
		 //� ������� unique_ptr::operator[] ��������� ��������� ������ ����������
		 //����� ���������� ������������ ������?

			__asm nop
		}

		{//1.e - ������� ������������ �������� � ���������������� delete-������� (�������)
		 //����� �������� ������ ���������� �� ����������� ��������� �������
		 //�������� unique_ptr ��� ������ �������
		 //���������� ���������������� delete-������� (�������) ��� ����������� 
		 //������������ ������

			std::string* arStrPtr[] = { new std::string("aa"), new std::string("bb"), new std::string("cc") };

			__asm nop
		}

		{//1.f �������� � ��������� ������, ���������� unique_ptr ��� ���������� �� std::string
			//����������� ��������� copy() ���������� �������� ������� � ������ ������ � ���������� 
			//���� �� ����
			//���������: ������������ ��������� � ������ std::make_move_iterator

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
	/*
	{

	//"��������":
	//������� writer1, writer2




	//�������� ����� �������� ��������� ������� ��������� ������ �� "���������" �������� � ����
	//���� �������


	__asm nop
	}//�������� �����???

	*/
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