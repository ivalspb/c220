#pragma once
#include <iostream>
#include <ctype.h>

using namespace std;

class MyString
{
    char* m_pStr;	//строка-член класса
    friend ostream& operator<<(ostream& stream, const MyString& str1);
public:
    MyString();
    MyString(const char* init_literal);
    MyString(const MyString &str_source);
    MyString(MyString&& tmp_str_source) noexcept;
    ~MyString();

    const char* GetString() const;
    void SetNewString(const char* new_str);

    MyString& operator=(const MyString& sr_str);
    MyString& operator=(MyString&& tmp_sr_str) noexcept;

    MyString& operator=(const char* sr_str);
    MyString operator+(const MyString& str2) const;
    MyString& operator+=(const MyString& str2);

    MyString operator--(int unused) const;
    MyString& operator++();

    bool operator<(const MyString& sr_str) const;
};

MyString Concat(const char*, ...);//Количество строк - любое! Признак конца - нулевая строка!


