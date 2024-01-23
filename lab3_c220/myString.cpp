#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include "myString.h"
#include <cstring>

using namespace std;

// Определение конструктора.
MyString::MyString()
{
	m_pStr = 0;
	//cout << "\nDefault string init\n";
}

MyString::MyString(const char* init_string)
{
	m_pStr = new char[strlen(init_string)+1];
	strcpy(m_pStr, init_string);
	//cout << "\nConst string init: " << m_pStr << endl;
}
MyString::MyString(const MyString& str_source)
{
	m_pStr= new char[strlen(str_source.m_pStr) + 1];
	strcpy(m_pStr, str_source.m_pStr);
	//cout << "\nConstructor of copy of string \"" << m_pStr << "\" is executed.\n";
}
MyString::MyString(MyString&& tmp_str_source) noexcept
{
	m_pStr = tmp_str_source.m_pStr;
	tmp_str_source.m_pStr = nullptr;
	//cout << "\nConstructor of move of string \"" << m_pStr << "\" is executed.\n";
}
// Определение деструктора.
MyString::~MyString()
{
	//if(m_pStr) cout << "\nString destructor: " << m_pStr << endl;
	//else  cout << "\nString destructor: NullStr" <<endl;
	delete[] m_pStr;
}
const char* MyString::GetString() const
{
	if (this) 
	{
		if (m_pStr) return m_pStr;
		else return "NullString!";
	}
	else return "NullPtr!";
}
void MyString::SetNewString(const char* new_str)
{
	delete[] m_pStr;
	m_pStr = new char[strlen(new_str) + 1];
	strcpy(m_pStr, new_str);
}

MyString Concat(const char* first_string, ...)
{
	const char** p = &first_string;
	size_t result_str_len = 0;
	while (*p)
	{
		result_str_len += strlen(*p);
		p++;
	}
	p = &first_string;
	char* result_str = new char[result_str_len+1] {0};
	while (*p)
	{
		strcat(result_str, *p);
		p++;
	}
	MyString return_str(result_str);
	delete[] result_str;
 	return return_str;
}

MyString& MyString::operator=(const MyString& sr_str)
{
	if(&sr_str!=this)
	{
		if (sr_str.m_pStr)
		{
			if (m_pStr)
			{
				if (strcmp(m_pStr, sr_str.m_pStr))
				{
					delete[] m_pStr;
					m_pStr = new char[strlen(sr_str.m_pStr) + 1];
					strcpy(m_pStr, sr_str.m_pStr);
				}//если строки и так равны, то ничего не присваиваем
			}
			else//если строка приемник пустая, то сравнивать некорректно (нечего)
			{
				m_pStr = new char[strlen(sr_str.m_pStr) + 1];
				strcpy(m_pStr, sr_str.m_pStr);
			}
		}
		else//если присваивается несуществующая строка, просто удаляем и обнуляем приемник 
		{
			delete[] m_pStr;
			m_pStr = 0;
		}
	}
	return *this;
}

MyString& MyString::operator=(MyString&& tmp_sr_str) noexcept
{
	if (this != &tmp_sr_str)
	{
		delete[] m_pStr;
		m_pStr = tmp_sr_str.m_pStr;
		tmp_sr_str.m_pStr = nullptr;
	}
	return *this;
}

MyString& MyString::operator=(const char* sr_str)
{
	if (sr_str)
	{
		if (this&&m_pStr)
		{
			if (strcmp(m_pStr, sr_str))
			{
				delete[] m_pStr;
				m_pStr = new char[strlen(sr_str) + 1];
				strcpy(m_pStr, sr_str);
			}//если строки и так равны, то ничего не присваиваем
		}
		else//если строка приемник пустая, то сравнивать некорректно (нечего)
		{
			m_pStr = new char[strlen(sr_str) + 1];
			strcpy(m_pStr, sr_str);
		}
	}
	else//если присваивается несуществующая строка, просто удаляем и обнуляем приемник 
	{
		delete[] m_pStr;
		m_pStr = 0;
	}
	return *this;
}

ostream& operator<<(ostream& stream, const MyString& str1)
{
	if (str1.m_pStr)	stream << str1.m_pStr <<" ";
	else stream << " contents: \"Null_String\"";
	return stream;
}

MyString MyString::operator+(const MyString& str2) const
{
	MyString tmp;
	//1) m_pStr=0 просто возвращяем str2
	if (!m_pStr) tmp=str2;
	else
	{
		if (!str2.m_pStr) tmp = *this;//2) str2.m_pStr=0 возвращяем копию текущей
		else//3) возвращяем конкатенацию
			tmp = Concat(m_pStr, str2.m_pStr,0);
	}
	return tmp;
}
MyString& MyString::operator+=(const MyString& str2)
{
	if (str2.m_pStr)
	{
		if (m_pStr)
		{
			char* tmp = new char[strlen(m_pStr) + strlen(str2.m_pStr) + 1] {0};
			strcpy(tmp, m_pStr);
			strcat(tmp, str2.m_pStr);
			delete[] m_pStr;
			m_pStr = tmp;
			tmp = 0;
		}
		else
		{
			m_pStr = new char[strlen(str2.m_pStr) + 1] {0};
			strcpy(m_pStr, str2.m_pStr);
		}
	}
	return *this;
}

MyString MyString::operator--(int unused) const
{
	MyString tmp(*this);
	char* p_temp_ch = tmp.m_pStr;
	while (*p_temp_ch)
	{
		if (isupper(*p_temp_ch))
			*p_temp_ch = tolower(*p_temp_ch);
		p_temp_ch++;
	}
	return tmp;
}
MyString& MyString::operator++()
{
	char* p_temp_ch = m_pStr;
	while (*p_temp_ch)
	{
		if (islower(*p_temp_ch))
			*p_temp_ch = toupper(*p_temp_ch);
		p_temp_ch++;
	}
	return *this;
}

bool MyString::operator<(const MyString& sr_str) const
{
	return strcmp(m_pStr, sr_str.m_pStr) < 0;
}