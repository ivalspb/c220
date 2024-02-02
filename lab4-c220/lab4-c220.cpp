#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <memory>
#include "my_constexpr.h"
#include "MyRange.h"

	using namespace std;

	int main()
	{


		//////////////////////////////////////////////////////////////////////////////////////////////
		//Задание 1. Реализуйте вычисление факториала с помощью constexpr-функции.
		//
		//Подсказки/напоминания: 
		//		- constexpr – функция должна состоять из единственной инструкции return <выражение>; (пока!)
		//		- но это выражение может включать вызов другой constexpr – функции, в частности рекурсивный
		//		  вызов 
		//		- если параметр рекурсивной constexpr- функции - это константа, компилятор вычислит результат
		//		  на этапе компиляции

		//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции (если в качестве
		//				параметра используется константа, известная компилятору на этапе компиляции).
		//				Для проверки достаточно создать встроенный массив с размерностью, вычисляемой
		//				посредством constexpr-функции:

		{	//Например:
			int ar[factr_cnstexpr(3)];

			//или
			constexpr int n = factr_cnstexpr(5);
			int ar1[n];

			//попробуйте:
			auto m = 7;
			//constexpr int n1 = factr_cnstexpr(m);
			//int ar1[n1];

			//а так?
			int n2 = factr_cnstexpr(m);
			__asm nop
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
		//Задание 2a. Перевод с помощью пользовательского литерала из двоичного представления строкового
		//в значение, например: строку "100000000" -> в значение 256
		//Проверить результат посредством префикса 0b
		//Чтобы вызов пользовательского литерала выглядел просто и читаемо, например: 100000000_b
		//логично использовать пользовательский литерал с единственным параметром - const char*

		//Так как речь идет о литералах, логично вычислять значения на этапе компиляции
		// => реализуйте пользовательский литерал посредством constexpr - функций
		//Подсказка/напоминание: 
		//		- constexpr – функция должна состоять из единственной инструкции return <выражение>;
		//		- но это выражение может включать вызов другой constexpr – функции,
		//		- которая может быть рекурсивной (если параметр такой функции - это константа,
		//		  компилятор вычислит результат вызова рекурсивной функции на этапе компиляции)

		{
			constexpr int dec_res = 00001001_b;
			__asm nop
		}

		//Задание 2b. Перевод в строковое двоичное представление, например: 256 -> "0b100000000"
		//Так как строка может быть любой длины, логичнее и проще возвращать объект std::string
		//=> возвращаемое значение не может быть constexpr!
		//Подсказка: манипулятора std::bin пока нет => преобразование в двоичную строку
		//придется делать вручную
		//Подсказка: количество разрядов в байте определяет константа CHAR_BIT - <cstdint>

		{
			std::string sBin= 9_toBinStr;
			__asm nop
		}


		//////////////////////////////////////////////////////////////////////////////////////////////
		//Задание 3. constexpr - объекты 
		//Создать класс (шаблон класса?) для хранения и манипулирования диапазоном значений.
		//В классе должны быть:
		//	переменные для хранения минимального и максимального значений,
		//	методы для получения каждого из значений
		//	метод для проверки - попадает ли указанное значение в диапазон
		//	метод, который получает любое значение данного типа и формирует результирующее значение:
		//							если принадлежит диапазону, то его и возвращаем
		//							если меньше минимального значения, возвращаем минимальное
		//							если больше максимального значения, возвращаем максимальное

		//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции. 

		{
			constexpr int min = -2;
			constexpr int max = 10;
			constexpr MyRange<int> m_rng(min, max);
			constexpr int get_min = m_rng.get_min();
			constexpr int get_max = m_rng.get_max();
			constexpr bool check = m_rng.is_entry(20);
			constexpr int ranged = m_rng.ranged(100);
			__asm nop
		}
		/***************************************************************/
	//Задание 4.
		/*
		Реализуйте шаблон функции для печати любых последовательностей (vector, list, deque, set и встроенного массива), которые могут содержать:
		•	как объекты любого типа,
		•	так и указатели на объекты любого типа (указатели распечатывать неинтересно => в этом случае следует получать значение по адресу)
		Подсказки: if constexpr
		*/
		{
			vector<string> v_val{"aaa_v", "bbb_v", "ccc_v"};
			list<string> l_val{"aaa_l", "bbb_l", "ccc_l"};
			deque<string> d_val{"aaa_d", "bbb_d", "ccc_d"};
			set<string> s_val{"aaa_s", "bbb_s", "ccc_s"};
			string ar_val[]={"aaa_ar", "bbb_ar", "ccc_ar"};

			printContainer(v_val);
			printContainer(l_val);
			printContainer(d_val);
			printContainer(s_val);
			printContainer(ar_val);

			vector<string*> v_ptr{new string("aaa_pv"), new string("bbb_pv"), new string("ccc_pv")};
			list<string*> l_ptr{new string("aaa_pl"), new string("bbb_pl"), new string("ccc_pl")};
			deque<string*> d_ptr{new string("aaa_pd"), new string("bbb_pd"), new string("ccc_pd")};
			set<string*> s_ptr{new string("aaa_ps"), new string("bbb_ps"), new string("ccc_ps")};
			string* ar_ptr[] = { new string("aaa_par"), new string("bbb_par"), new string("ccc_par") };

			printContainer(v_ptr);
			printContainer(l_ptr);
			printContainer(d_ptr);
			printContainer(s_ptr);
			printContainer(ar_ptr);

			for (auto& i : v_ptr) delete i;
			for (auto& i : l_ptr) delete i;
			for (auto& i : d_ptr) delete i;
			for (auto& i : s_ptr) delete i;
			for (auto& i : ar_ptr) delete i;
		
			__asm nop
		}

		/***************************************************************/
		//Задание 5.
			/* Реализуйте шаблон функции сложения двух значений.
			Если первое слагаемое является вектором, то все элементы вектора нужно увеличить на значение второго параметра.
			При этом элементы вектора и второй параметр должны быть одного и того же типа.
			Подсказки: if constexpr, is_same
			*/
		{
			constexpr int i1 = 2;
			constexpr double d1 = 3.3;
			std::vector<int> v1{ 1,2,3 };
			std::vector<double>u1{ 1.1,2.2,3.3 };

			constexpr bool b = std::is_same_v<decltype(v1), std::vector<int>>;

			auto res1 = my_sum(i1, d1);
			auto res2 = my_sum(v1,i1);
			auto res3 = my_sum(d1, u1);
			//auto res4 = my_sum(v1, u1);
			//auto res5 = my_sum(v1, d1);
			__asm nop

		}


		/***************************************************************/
	//Задание 6.
		/* 	Реализуйте шаблон функции вывода на печать значений элементов любого адаптера (stack, queue, priority_queue)
		Подсказки: if constexpr, is_same
		Предусмотрите вывод значений, если в адаптере хранятся указатели.
		*/
		{
			stack<string> stack_val({"aaa_stack", "bbb_stack", "ccc_stack"});
			queue<string> queue_val({ "aaa_queue", "bbb_queue", "ccc_queue" });
			std::initializer_list il1{ "aaa_priority_queue", "bbb_priority_queue", "ccc_priority_queue" };
			priority_queue<string> priority_queue_val(il1.begin(),il1.end());
			
			printAdapterContainer(stack_val);
			printAdapterContainer(queue_val);
			printAdapterContainer(priority_queue_val);
			
			std::initializer_list il2{ new string("aaa_pstack"), new string("bbb_pstack"), new string("ccc_pstack") };
			stack<string*> stack_ptr(il2);
			std::initializer_list il3{ new string("aaa_pqueue"), new string("bbb_pqueue"), new string("ccc_pqueue") };
			queue<string*> queue_ptr(il3);
			std::initializer_list il4{new string("aaa_ppriority_queue"), new string("bbb_ppriority_queue"), new string("ccc_ppriority_queue")};
			priority_queue<string*> priority_queue_ptr(il4.begin(),il4.end());

			printAdapterContainer(stack_ptr);
			printAdapterContainer(queue_ptr);
			printAdapterContainer(priority_queue_ptr);
	
			for (auto& i : il2) delete i;
			for (auto& i : il3) delete i;
			for (auto& i : il4) delete i;
		
			__asm nop
		}

		/***************************************************************/
	//Задание 7.
		/* 	Реализуйте шаблон constexpr функции Smth(), которая должна возвращать значения разного типа
		Подсказки: constexpr, if constexpr
		*/
		//constexpr int res1 = /*<вызов Smth()>;*/ //res1 = 1
		//constexpr double res2 = /*<вызов Smth()>; */ //res2 = 2.2
		//  /*constexpr???*/ std::string res3 = /*<вызов Smth()>; */ //res3 = "abc"


		//***************************************************************/
		//Задание 8.

			/*Пользовательский deduction guide – для вывода типов параметров шаблона
			Задан шаблон класса, который инкапсулирует внедренный ограниченный массив известной
			размерности с элементами любого типа. */
			/*
			template<typename T, size_t size> class MyArray
				{
					T ar[size]; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
					…
					public:
					MyArray(const T*[, возможно другие параметры]);


				};

			*/
			/*
			//Требуется обеспечить работоспособность приведенных примеров использования.
				{
					MyArray<int, 5> ar1;//MyArray<int,5>
	MyArray<char, 5> ar2{"ABCqwerty"};//MyArray<char,5>

					MyArray ar3{"ABC"}; //MyArray<char,4>

	int ar[] = { 1,2,3 };
					MyArray ar4{ ar };

				}
			*/


	}


