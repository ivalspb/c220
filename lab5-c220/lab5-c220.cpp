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
	//Задание 1. unique_ptr
	{

		//1.а - обеспечьте корректное выполнение фрагмента
		{

			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };

			//Распечатайте все строки
			for (const auto& i : v) 
				std::cout << *i << " ";
			//???
			for (auto& i : v) 
				delete i;
			__asm nop
			
		} //???

		//1.b - модифицируйте задание 1.а:
		 //обеспечьте посредством std::unique_ptr: 
		 //эффективное заполнение (вспомните про разные способы формирования std::unique_ptr), 
		 //безопасное хранение указателей на динамически создаваемые объекты std::string, 
		 //манипулирование,
		 //и освобождение ресурсов
		 //

		{
			std::vector<std::unique_ptr<std::string>> v;
			v.push_back(std::make_unique<std::string>("aa"));
			v.push_back(std::make_unique<std::string>("bb"));
			v.push_back(std::make_unique<std::string>("cc"));

			//Распечатайте все строки
			std::cout << std::endl;
			for (const auto& i : v)
				std::cout << *i << " ";
			__asm nop
			//??? Уничтожение динамически созданных объектов?
		} //???

		{//1.c - дополните задание 1.b добавьте возможность изменять хранящиеся строки
		 //следующим образом (например, добавить указанный суффикс: "AAA" -> "AAA_1")  
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

		{//1.d - динамический массив объектов	

		 //Создайте unique_ptr, который является оберткой для динамического массива
		 //с элементами std::string

			size_t n = 10;
			auto p_dyn_ar_str = std::make_unique<std::string[]>(n);

		 //С помощью unique_ptr::operator[] заполните обернутый массив значениями
		 
			std::cout << std::endl;
			for (size_t i = 0; i < n; i++)
			{
				p_dyn_ar_str[i] = "Test string "+std::to_string(i)+",";
				std::cout << p_dyn_ar_str[i]<<" ";
			}
		 //Когда происходит освобождения памяти?

			__asm nop
		}

		{//1.e - массивы динамических объектов и пользовательская delete-функция (функтор)
		 //Задан стековый массив указателей на динамически созданные объекты
		 //Создайте unique_ptr для такого массива
		 //Реализуйте пользовательскую delete-функцию (функтор) для корректного 
		 //освобождения памяти

			std::string* arStrPtr[] = { new std::string("aad"), new std::string("bbd"), new std::string("ccd") };
			size_t n = std::size(arStrPtr);
			auto deleter_dyn_str = [n](auto& x) {for (size_t i = 0; i < n; i++) delete x[i]; };
			std::unique_ptr<std::string*[], decltype(deleter_dyn_str)> p_arStrPtr (arStrPtr, deleter_dyn_str);
			__asm nop
		}

		{
			//1.f Создайте и заполните вектор, содержащий unique_ptr для указателей на std::string
//*
			typedef  std::unique_ptr<std::string> u_p_str_t;
			std::vector<u_p_str_t>v_u_p_str;
			v_u_p_str.push_back(std::make_unique<std::string>("v_u_p_str_aaa"));
			v_u_p_str.push_back(std::make_unique<std::string>("v_u_p_str_bbb"));
			v_u_p_str.push_back(std::make_unique<std::string>("v_u_p_str_ccc"));
			
			std::cout << "\n\nThe vector of unique_ptr to string*\n";
			for (const auto& i : v_u_p_str)
				std::cout << *i << " ";

			//Посредством алгоритма copy() скопируйте элементы вектора в пустой список с элементами 
			//того же типа
			//Подсказка: перемещающие итераторы и шаблон std::make_move_iterator
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
	//Задание 2.shared_ptr + пользовательская delete-функция 

	//Реализовать возможность записи в файл данных (строчек) из разных источников 
	//Так как все "писатели" будут по очереди записывать свои данные в один и тот же файл,
	//логично предоставить им возможность пользоваться одним и тем же объектом потока вывода =>
	//безопасной оберткой для такого указателя является shared_ptr
	//а. Первый владелец должен открыть/создать файл для записи
	//б. Все остальные писатели должны присоединиться к использованию
	//в. Последний владелец указателя должен закрыть файл

	//Подсказка: имитировать порядок записи можно с помощью функции rand()
	
	{

	//"писатели":
	//Создать writer1, writer2

		std::string fn("tmpfile.txt");
		typedef std::shared_ptr<std::ofstream> writer_t;
		std::vector<writer_t> writers(rand() % 30, writer_t(new std::ofstream(fn), FileDeleter(fn)));
		//инициализировать было не обязательно, так как делетер не входит в тип и может быть произвольным 
		for (size_t session_number = 0; session_number < writers.size(); session_number++)
		{
			size_t session_writer = rand() % writers.size();
			(*writers[session_writer]) << "\nWriter #" << session_writer << ":\n";
			for (size_t session_strings = 0; session_strings < rand() % 10; session_strings++)
			{
				//заданное число итераций случайным образом позволяем одному из "писателей" записать в файл
				//свою строчку
				(*writers[session_writer]) << rand() % 100 << " ";
			}
		}

		__asm nop
	}//закрытие файла???

	__asm nop

	/***************************************************************/
	//Задание 3.
	{
		//Дан массив элементов типа string
		std::string strings[] = { "abc", "123", "qwerty", "#$%" };
		//До завершения фрагмента строки должны существовать в единственном экземпляре.
		//Требуется обеспечить манипулирование строками а) без копирования и б) без изменения порядка
		//элементов в массиве!

		//В std::set "складываем" по алфавиту обертки для строк, которые содержат только буквы 
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

		//В std::vector "складываем" обертки для строк, которые содержат только цифры 
		//Выводим на экран
		//Находим сумму

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
		//сюда "складываем" обертки для строк, которые не содержат ни символов букв, ни символов цифр
		//и просто выводим
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
	//Задание 4. 
	{
		//Дано:
		std::string ar[] = { "my","Hello", "World" };
		std::vector < std::shared_ptr<std::string>> v = { std::make_shared<std::string>("good"), std::make_shared<std::string>("bye") };



		//а) Требуется добавить в вектор обертки для элементов массива, НЕ копируя элементы массива! 
		
		for (const auto& i : ar)
			v.push_back(std::make_shared<std::string>(i));
		 
		//б) Отсортировать вектор по алфавиту и вывести на экран
		
		std::sort(v.begin(), v.end(), [](auto& a, auto& b) {return *a < *b; });
		std::cout << "\n4. Sorted vector:\n";
		for (const auto& i : v) std::cout << *i << " ";

		//в) Обеспечить корректное освобождение памяти


		__asm nop
	}
	/***************************************************************/
		//Задание 5. shared_ptr и weak_ptr
		//Создаем генеалогическое дерево посредством класса human. В классе хранятся:
		//имя - stringuuuu
		//возможно признак: жив или уже нет...
		//родители - shared_ptr (родители не всегда известны...)
		//дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

		//Методы класса human:
		//конструктор - для инициализации имени и признака
		//конструктор копирования, оператор присваивания, move ???
		//статический метод child() - 
		//				должен создать создать и вернуть обертку для родившегося человека
		//				+ сформировать все связи ребенка с родителями и наоборот

		//Ввести возможность распечатать генеалогическое дерево для указанного индивидума

	{
		//История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
		//(то есть на самом деле два деда и две бабы):


		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...

		//у них появились дети - child():


		//а у детей в свою очередь свои дети:


		//...
		__asm nop
	}





	__asm nop

}