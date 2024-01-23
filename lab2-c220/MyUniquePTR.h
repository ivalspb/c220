//Задача – класс должен обеспечивать единоличное владение динамически создаваемым объектом.
//std::unique_ptr
#pragma once


template <typename T>
class MyUniquePTR
{
	T* mp;
public:
	MyUniquePTR() :mp(nullptr) {};
	MyUniquePTR(const MyUniquePTR& other) = delete;
	MyUniquePTR(MyUniquePTR&& tmp_other);
	MyUniquePTR& operator=(const MyUniquePTR& other) = delete;
	MyUniquePTR& operator=(MyUniquePTR&& tmp_other);

};

