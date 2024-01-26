#include "MyQueue.h"
#include <iostream>
#include "myString.h"

int main()
{
    {
        // Следующий фрагмент должен работать не только КОРРЕКТНО, но и ЭФФЕКТИВНО:
        MyQueue<MyString> q1 { MyString("AAA"), MyString("qwerty")/*,
            < другие_инициализаторы>*/ }; // конструктор по списку инициализации
        for (const auto& el : q1) { std::cout << el << ' '; } // range-based for
        MyString s("abc");
        q1.push(s);
        q1.printMyQueue();
        q1.push(MyString("123")); // rvalue push
        q1.printMyQueue();
        try {
            MyString s1 = q1.pop();
            q1.printMyQueue();
            q1.pop();
            q1.printMyQueue();
        }
        catch (const exception& e)
        {
            cerr << endl << "Caught: " << e.what() << endl;
            cerr << "Type: " << typeid(e).name() << endl;
        }
        q1.push("qqq");
        q1.printMyQueue();
        q1.push("qqq");
        q1.printMyQueue();

        MyQueue < MyString > q2 = q1;
        q2.printMyQueue();

        MyQueue < MyString > q22 = std::move(q1);
        q1.printMyQueue();
        q22.printMyQueue();

        MyQueue < MyString > q3 { 10, MyString("!") }; // очередь должна содержать 10 элементов со строкой «!»
        q3.printMyQueue();
        q1 = q3;
        q1.printMyQueue();
        q2 = MyQueue < MyString >(5, MyString(" ? "));
        q2.printMyQueue();
        q1 = { MyString("bbb"), MyString("ssss") }; // оператор присваивания по списку инициализации
        q1.printMyQueue();
    }//проверка утечек памяти
}

