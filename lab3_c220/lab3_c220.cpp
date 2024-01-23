#include "MyQueue.h"
#include <iostream>
#include "myString.h"

int main()
{
    // Следующий фрагмент должен работать не только КОРРЕКТНО, но и ЭФФЕКТИВНО:
    MyQueue<MyString> q1 { MyString("AAA"), MyString("qwerty")/*,
        < другие_инициализаторы>*/ }; // конструктор по списку инициализации
    for (const auto& el : q1) { std::cout << el << ' '; } // range-based for
    MyString s("abc");
    q1.push(s);
    q1.push(MyString("123")); // rvalue push
    MyString s1 = q1.pop();
    q1.push("qqq");
    MyQueue < MyString > q2 = q1;
    MyQueue < MyString > q22 = std::move(q1);
    MyQueue < MyString > q3 { 10, MyString("!") }; // очередь должна содержать 10 элементов
    // со строкой «!»
    q1 = q3;
    q2 = MyQueue < MyString >(5, MyString(" ? "));
    q1 = { MyString("“bbb”"), MyString("“ssss”") }; // оператор присваивания по списку инициализации

}

