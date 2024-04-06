//Стандартная библиотека шаблонов - STL 
	//Контейнеры стандартной библиотеки - vector
	//Итераторы

#include <iostream>
#include <vector>
#include <stdexcept> // Для std::out_of_range
#include <algorithm> // Для использования функции find
#include <list>
#include <deque>


#pragma warning(disable: 4786)


using namespace std;


template <typename T>
void printVectorInfo(const std::vector<T>& vec) {
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;
	std::cout << "Max Size: " << vec.max_size() << std::endl;
	std::cout << "Elements: ";
	for (const auto& elem : vec) {
		std::cout << elem << " ";
	}
	std::cout << std::endl << std::endl;
}

template<typename T>
void insertIfNotExists(std::vector<T>& vec, const T& value) {
	// Проверяем, есть ли значение в векторе
	if (std::find(vec.begin(), vec.end(), value) == vec.end()) {
		// Если значения нет, вставляем его в начало вектора
		vec.insert(vec.begin(), value);
	}
}



class MyString {
private:
	std::string str;
public:
	MyString(const std::string& s) : str(s) {}
	const std::string& get() const { return str; }
	void set(const std::string& s) { str = s; }

	bool operator==(const MyString& other) const {
		return str == other.str;
	}
};


class Point {
public:
	double x, y;
	Point() : x(0), y(0) {} // Конструктор по умолчанию
	Point(double x_val, double y_val) : x(x_val), y(y_val) {} // Конструктор с параметрами
	Point(int x_val = 0, int y_val = 0) : x(x_val), y(y_val) {}

	// Перегрузка оператора << для вывода элементов типа Point
	friend std::ostream& operator<<(std::ostream& os, const Point& point) {
		os << "(" << point.x << ", " << point.y << ")";
		return os;
	}

	// Перегрузка оператора << для вывода элементов типа Point*
	friend std::ostream& operator<<(std::ostream& os, const Point* point) {
		os << "(" << point->x << ", " << point->y << ")";
		return os;
	}


	bool operator<(const Point& other) const {
		return x < other.x;
	}
	

	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}
};


// Перегрузка оператора << для вывода элементов вектора
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "{";
	for (size_t i = 0; i < vec.size(); ++i) {
		os << vec[i];
		if (i != vec.size() - 1) {
			os << ", ";
		}
	}
	os << "}";
	return os;
}

std::string removeRepeatingSequences(const std::vector<char>& input) {
	std::string result;
	if (input.empty()) {
		return result; // Возвращаем пустую строку, если вектор пустой
	}

	char prevChar = input[0];
	result.push_back(prevChar); // Добавляем первый символ в результат

	for (size_t i = 1; i < input.size(); ++i) {
		if (input[i] != prevChar) {
			result.push_back(input[i]); // Добавляем символ в результат, если он не равен предыдущему
			prevChar = input[i]; // Обновляем предыдущий символ
		}
	}

	return result;
}

template<typename T>
void removeDuplicates(std::vector<T>& vec) {
	// Сортируем вектор
	std::sort(vec.begin(), vec.end());

	// Используем std::unique() для перемещения всех дублирующихся элементов в конец вектора
	auto last = std::unique(vec.begin(), vec.end());

	// Используем метод erase() для удаления всех дубликатов
	vec.erase(last, vec.end());
}

template<typename Container>
void printContainer(const Container& cont, const std::string& contName) {
	std::cout << "Container type: " << typeid(Container).name() << std::endl;
	std::cout << "Container name: " << contName << std::endl;
	std::cout << "Container elements: ";

	for (const auto& elem : cont) {
		std::cout << elem << " ";
	}

	std::cout << std::endl << std::endl;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& vv) {
	for (const auto& innerVec : vv) {
		for (const auto& element : innerVec) {
			os << element << " ";
		}
		os << std::endl;
	}
	return os;
}

// Функция-предикат для удаления элементов меньше нуля
bool isNegative(int x) {
	return x < 0;
}

int main()
{
	// Контейнер стандартной библиотеки vector 

//////////////////////////////////////////////////////////////////////
	//Создание векторов. 

	//Создайте следующие вектора:
	//---------------------------
	//пустой вектор целых чисел - vInt и проверьте с помощью функции size(),
	//что его размер нулевой. 

	std::vector<int> vInt; // создание пустого вектора целых чисел
	std::cout << "Size of vInt: " << vInt.size() << std::endl; // проверка размера




	//Раскомментируйте следующий фрагмент, подумайте - все ли корректно
	//Если есть некорректности, - исправьте

	//vInt.front()=1;
	//Попытка доступа к front() элементу до заполнения вектора будет некорректной, так как вектор пустой:


	//С помощью функции push_back() в цикле заполните вектор какими-либо значениями.
	//На каждой итерации цикла следите за размером вектора с помощью методов
	//size(), capacity(), max_size() и выводите значения элементов. 
	//
	//Подсказка: так как такая проверка понадобится Вам и в следующих заданиях,
	//напишите шаблон функции, которая для вектора, содержащего элементы любого типа
	//выводит его "реквизиты" и значения элементов на консоль.

	std::vector<int> myVector;

	for (int i = 0; i < 10; ++i) {
		myVector.push_back(i * 2);
		printVectorInfo(myVector);
	}

	



	//вектор вещественных - vDouble1 с заданным Вами начальным размером  и
	//проверьте результат с помощью созданного Вами шаблона. Как будут
	//проинициализированы элементы вектора?
	// Создаем вектор вещественных чисел с начальным размером 5
	std::vector<double> vDouble1(5);

	// Печатаем информацию о векторе
	printVectorInfo(vDouble1);



	//вектор объектов типа MyString с начальным размером - 5 элементов
	//и инициализацией каждого элемента строкой "A"
	//C помощью функции at() а также с помощью оператора
	//индексирования []  измените значения каких-либо элементов.
	//Попробуйте "выйти" за границы вектора с помощью at() и
	//с помощью []. 
	std::vector<MyString> vecMyString(5, MyString("A"));

	// Изменяем значения некоторых элементов с помощью функции at()
	try {
		vecMyString.at(2).set("B");
		vecMyString.at(4).set("C");
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Caught an out_of_range exception: " << e.what() << std::endl;
	}

	// Изменяем значение элемента с помощью оператора индексирования []
	vecMyString[0].set("X");

	// Попробуем обратиться к элементам за пределами вектора
	try {
		vecMyString.at(10).set("D");
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Caught an out_of_range exception: " << e.what() << std::endl;
	}

	// Печатаем значения всех элементов вектора
	for (const auto& elem : vecMyString) {
		std::cout << elem.get() << std::endl;
	}




	//вектор вещественных - vDouble3, который является копией элементов
	// [0,5) массива вещественных чисел dMas. Предворительно массив dMas 
	//нужно создать и проинициализировать!
	// Создаем и инициализируем массив вещественных чисел dMas
	const int size = 5;
	double dMas[size];
	for (int i = 0; i < size; ++i) {
		dMas[i] = i * 1.1; // Произвольная инициализация значений массива
	}

	// Создаем вектор vDouble3, который является копией элементов массива dMas
	std::vector<double> vDouble3(dMas, dMas + size);

	// Печатаем значения элементов вектора vDouble3
	std::cout << "Values in vDouble3: ";
	for (const auto& elem : vDouble3) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;




	//вектор вещественных - vDouble4, который является копией элементов
	// [2,5) вектора vDouble3. 
	std::vector<double> vDouble3_1 = { 1.1, 2.2, 3.3, 4.4, 5.5 };

	// Создаем вектор vDouble4, который является копией элементов с индексами от 2 до 4 вектора vDouble3
	std::vector<double> vDouble4(vDouble3_1.begin() + 2, vDouble3_1.begin() + 5);

	// Печатаем значения элементов вектора vDouble4
	std::cout << "Values in vDouble4: ";
	for (const auto& elem : vDouble4) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;




	//вектор элементов типа Point - vPoint1 а) с начальным размером 3. Какой конструктор
	//будет вызван для каждого элемента?
	//b) vPoint2 с начальным размером 5 и проинициализируйте каждый элемент координатами (1,1).
	std::vector<Point> vPoint2(5, Point(1, 1));

	// Выводим координаты каждого элемента
	for (const auto& point : vPoint2) {
		std::cout << "x: " << point.x << ", y: " << point.y << std::endl;
	}




	//вектор указателей на Point - vpPoint с начальным размером 5
	//Подумайте: как корректно заставить эти указатели "указывать" на объекты Point
	{

		//Подсказка: для вывода на печать значений скорее всего Вам понадобится
			//а) специализация Вашей шаблонной функции
			//б) или перегрузка operator<< для Point*

		 // Создаем вектор указателей на объекты типа Point
		std::vector<Point*> vpPoint(5);

		// Создаем объекты типа Point и добавляем указатели на них в вектор
		for (int i = 0; i < 5; ++i) {
			vpPoint[i] = new Point(i + 1, i + 1);
		}

		// Выводим значения объектов, на которые указывают элементы вектора
		for (const auto& point : vpPoint) {
			std::cout << point << std::endl;
		}

		


		// Освобождаем память, выделенную под объекты Point
		for (auto& point : vpPoint) {
			delete point;
		}

	}//Какие дополнительные действия нужно предпринять для такого вектора?


	///////////////////////////////////////////////////////////////////////
	//Резервирование памяти.
	//Подумайте, всегда ли верны приведенные ниже проверки?
		/*
		{
		size_t n=...
		vector<int> v(n);
		v.resize(n/2);
		if(v.capacity() == n) //true?
		}
		*/
		//Это утверждение будет истинным, если вектор v после вызова resize(n / 2) не изменяет свою емкость. Верно, если емкость вектора не меняется после уменьшения размера, но это не всегда гарантируется, так как вектор может переместить свои элементы в другое место памяти, если емкости не хватает для уменьшения.
			

		/*
		{
		int n=...
		size_t m=...
		vector<int> v(n);
		v.reserve(m);
		if(v.capacity() == m) //true?
		}
		*/
		// Это утверждение будет верным, если после вызова reserve(m) емкость вектора v действительно равна m.

		/*
		{
		vector<int> v(3,5);
		v.resize(4,10); //значения?
		v.resize(5); //значения?

		}
		*/
		//После выполнения этого блока кода v будет содержать элементы [5, 5, 5, 10, 0].

		//Создайте два "пустых" вектора с элементами
		//любого (но одного и того же типа) типа. 
		//В первом векторе зарезервируйте память под 5 элементов, а потом заполните
		//его значениями с помощью push_back.
		//Второй вектор просто заполните значениями посредством push_back.
		//
		//Сравните размер, емкость векторов и значения элементов
			
		std::vector<int> v1;
		std::vector<int> v2;

		v1.reserve(5); // Резервирование памяти под 5 элементов

		// Заполнение первого вектора значениями с помощью push_back
		for (int i = 0; i < 5; ++i) {
			v1.push_back(i * 2);
		}

		// Заполнение второго вектора значениями с помощью push_back
		for (int i = 0; i < 5; ++i) {
			v2.push_back(i * 3);
		}

		// Вывод информации о первом векторе
		std::cout << "v1.size() = " << v1.size() << ", v1.capacity() = " << v1.capacity() << std::endl;
		std::cout << "v1 elements: ";
		for (const auto& elem : v1) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		// Вывод информации о втором векторе
		std::cout << "v2.size() = " << v2.size() << ", v2.capacity() = " << v2.capacity() << std::endl;
		std::cout << "v2 elements: ";
		for (const auto& elem : v2) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;


		/*Использование функции reserve в стандартном контейнере std::vector целесообразно, когда мы заранее знаем ожидаемое количество элементов, которые будут храниться в векторе. Резервирование памяти позволяет избежать частых перевыделений памяти при добавлении элементов в вектор методом push_back. Это может быть особенно полезно при работе с большими объемами данных или в критических участках кода, где производительность имеет значение.

Однако, в нашем конкретном случае использование reserve не является необходимым, так как мы добавляем всего 5 элементов в каждый из векторов. std::vector обычно умеет хорошо управлять памятью и автоматически увеличивает свою емкость по мере необходимости. Таким образом, в данном случае можно обойтись без явного вызова reserve.

Кроме того, важно помнить, что capacity() не обязательно равна size(). capacity() отображает текущий размер выделенной памяти, в то время как size() отображает фактическое количество элементов в векторе.*/

		







		//!!! shrink_to_fit - Уменьшение емкости вектора.
		//Для любого вектора из предыдущего задания требуется уменьшить емкость
		//до size.
		std::vector<int> v1_1 = { 0, 2, 4, 6, 8 }; // Пример для v1
		std::vector<int> v2_1 = { 1, 3, 5, 7, 9 }; // Пример для v2

		// Уменьшение емкости вектора v1 до его текущего размера
		v1.shrink_to_fit();

		// Уменьшение емкости вектора v2 до его текущего размера
		v2.shrink_to_fit();

		// Вывод информации о емкости векторов после уменьшения
		std::cout << "After shrinking to fit:" << std::endl;
		std::cout << "v1.size() = " << v1_1.size() << ", v1.capacity() = " << v1_1.capacity() << std::endl;
		std::cout << "v2.size() = " << v2_1.size() << ", v2.capacity() = " << v2_1.capacity() << std::endl;




		//Создание "двухмерного вектора" - вектора векторов
		//Задан одномерный массив int ar[] = {11,2,4,3,5};
		//Создайте вектор векторов следующим образом:
		//вектор vv[0] - содержит 11 элементов со значением 11
		//vv[1] - содержит 2,2
		//vv[2] - содержит 4,4,4,4
		//...
		//Распечатайте содержимое такого двухмерного вектора по строкам
		//с помощью:

		//std::cout<<vv<<std::endl;

		int ar[] = { 11, 2, 4, 3, 5 };

		// Создаем вектор векторов
		std::vector<std::vector<int>> vv;

		// Заполняем вектор векторов в соответствии с заданным массивом
		for (size_t i = 0; i < sizeof(ar) / sizeof(ar[0]); ++i) {
			vv.push_back(std::vector<int>(i + 1, ar[i]));
		}


		// Вывод двумерного вектора с помощью оператора <<
		std::cout << vv;


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//Вставка элемента последовательности insert().
			//Реализуйте функцию, которая должна вставлять новый элемент
				//в начало вектора только при условии, что в векторе такого
				 //значения еще нет.
			//Проверьте работоспособность функции - в вектор vChar2 вставьте в начало вектора символ только при
			//условии, что в векторе такого символа еще нет.
				 //например: vChar2 - abc 
				 //При попытке вставить 'a' попытка должна быть проигнорирована
				 //При попытке вставить 'q' vChar2 - qabc 



			//Реализуйте функцию, которая должна вставлять новый элемент
				 //перед каждым элементом вектора
			//Проверьте работоспособность функции - вставьте перед каждым элементом вектора vChar2 букву 'W'

		std::vector<char> vChar2 = { 'a', 'b', 'c' };


		insertIfNotExists(vChar2, 'a');


		insertIfNotExists(vChar2, 'q');

		// Выводим содержимое вектора после вставки
		for (const auto& elem : vChar2) {
			std::cout << elem;
		}
		std::cout << std::endl;



		///////////////////////////////////////////////////////////////////
			//Напишите функцию, которая должна удалять только повторяющиеся последовательности.
			//Например: было - "qwerrrrty12222r3", стало - "qwety1r3"

		std::vector<char> input = { 'q', 'w', 'e', 'r', 'r', 'r', 'r', 't', 'y', '1', '2', '2', '2', '2', 'r', '3' };
		std::string result = removeRepeatingSequences(input);

		std::cout << "Before: " << input << std::endl;
		std::cout << "After: " << result << std::endl;





		///////////////////////////////////////////////////////////////////

			//Удаление элемента последовательности erase()
			//Напишите функцию удаления из любого вектора всех дублей 
				 //Например: было - "qwerrrrty12222r3", стало - "qwerty123"

		std::vector<char> vChar = { 'q', 'w', 'e', 'r', 'r', 'r', 'r', 't', 'y', '1', '2', '2', '2', '2', 'r', '3' };

		// Удаление дубликатов из вектора
		removeDuplicates(vChar);

		// Выводим содержимое вектора после удаления дубликатов
		for (std::vector<char>::const_iterator it = vChar.begin(); it != vChar.end(); ++it) {
			std::cout << *it;
		}
		std::cout << std::endl;






		///////////////////////////////////////////////////////////////////
			//Создайте новый вектор таким образом, чтобы его элементы стали
			//копиями элементов любого из созданных ранее векторов, но расположены
			//были бы в обратном порядке
		std::vector<int> originalVec = { 1, 2, 3, 4, 5 };

		// Создаем новый вектор с элементами в обратном порядке
		std::vector<int> reversedVec(originalVec.rbegin(), originalVec.rend());

		// Выводим содержимое нового вектора
		std::cout << "Reversed vector:" << std::endl;
		for (const auto& elem : reversedVec) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;






		///////////////////////////////////////////////////////////////////

			//Задание 1. Списки. Операции, характерные для списков.
			//Создайте пустой список из элементов Point - ptList1 и наполните
			//его значениями с помощью методов push_back(),
			//push_front, insert()


			//Напишите шаблон функции, которая будет выводить элементы
			//ЛЮБОГО КОНТЕЙНЕРА на печать. Проверьте работу шаблона на контейнерах
			//vector и list. Подсказка - хотелось бы увидеть тип контейнера.


			//Сделайте любой из списков "реверсивным" - reverse()


			//Создайте список ptList2 из элементов Point таким образом, чтобы он стал 
			//копией вектора элементов типа Point, но значения элементов списка располагались
			//бы в обратном порядке 



			//Отсортируйте списки  ptList1 и ptList2 - методом класса list - sort()
			//по возрастанию.
			//Подумайте: что должно быть перегружено в классе Point для того, чтобы
			//работала сортировка

		std::list<Point> ptList1;
		ptList1.push_back(Point(1, 1));
		ptList1.push_front(Point(2, 2));
		ptList1.insert(++ptList1.begin(), Point(3, 3));

		// Вывод элементов ptList1
		printContainer(ptList1, "ptList1");

		// Делаем ptList1 реверсивным
		ptList1.reverse();
		std::cout << "After reversing ptList1:" << std::endl;
		printContainer(ptList1, "ptList1");

		// Создаем список ptList2, копируя элементы из вектора в обратном порядке
		std::vector<Point> points = { Point(4, 4), Point(5, 5), Point(6, 6) };
		std::list<Point> ptList2(points.rbegin(), points.rend());

		// Вывод элементов ptList2
		printContainer(ptList2, "ptList2");

		// Сортировка списков ptList1 и ptList2 по возрастанию
		ptList1.sort();
		ptList2.sort();


		// Вывод отсортированных списков
		std::cout << "After sorting ptList1:" << std::endl;
		printContainer(ptList1, "ptList1");
		std::cout << "After sorting ptList2:" << std::endl;
		printContainer(ptList2, "ptList2");



		//Объедините отсортированные списки - merge(). Посмотрите: что
		//при этом происходит с каждым списком.

		std::list<int> list1 = { 1, 3, 5 };
		std::list<int> list2 = { 2, 4, 6 };
		list1.merge(list2); // list1 теперь содержит объединенный и отсортированный список, а list2 становится пустым





		//Исключение элемента из списка - remove()
		//Исключите из списка элемент с определенным значением.
		//Подумайте: что должно быть перегружено в классе Point?
		std::list<MyString> myList = { MyString("Hello"), MyString("World"), MyString("Hello") };

		// Явное использование оператора == и вызов erase для элементов, которые равны MyString("Hello")
		for (auto it = myList.begin(); it != myList.end(); ) {
			if (*it == MyString("Hello")) {
				it = myList.erase(it);
			}
			else {
				++it;
			}
		}

		// Вывод содержимого списка после удаления
		for (const auto& str : myList) {
			std::cout << str.get() << " ";
		}
		std::cout << std::endl;






		//Исключение элемента из списка, удовлетворяющего заданному условию:
		//любая из координат отрицательна - remove_if(). 
		// Удаление элементов из списка, которые меньше нуля
		std::list<int> myList_1 = { -1, 2, -3, 4, -5 };

		// Удаление элементов из списка, которые меньше нуля
		myList_1.remove_if(isNegative);

		// Вывод списка после удаления элементов
		for (const auto& elem : myList_1) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

		//Исключение из списка подряд расположенных дублей - unique(). 
		std::list<int> myList_2 = { 1, 2, 2, 3, 3, 3, 4, 4, 5 };
		myList_2.unique(); // Удаляет подряд расположенные дубликаты, список становится {1, 2, 3, 4, 5}




		///////////////////////////////////////////////////////////////////
			//Задание 2.Очередь с двумя концами - контейнер deque

			//Создайте пустой deque с элементами типа Point. С помощью
			//assign заполните deque копиями элементов вектора. С помощью
			//разработанного Вами в предыдущем задании универсального шаблона
			//выведите значения элементов на печать



			//Создайте deque с элементами типа MyString. Заполните его значениями
			//с помощью push_back(), push_front(), insert()
			//С помощью erase удалите из deque все элементы, в которых строчки
			//начинаются с 'A' или 'a'
					
		 // Задание 2: Создание пустого deque с элементами типа Point
		std::deque<Point> pointDeque;

		// Создание вектора с элементами типа Point
		std::vector<Point> points_1 = { Point(1, 1), Point(2, 2), Point(3, 3) };

		// Заполнение deque копиями элементов вектора с помощью assign
		pointDeque.assign(points_1.begin(), points_1.end());

		// Вывод значений элементов на печать с помощью шаблона функции
		printContainer(pointDeque, "pointDeque");


		std::deque<MyString> myDeque;

		// Заполнение deque значениями с помощью push_back(), push_front(), insert()
		myDeque.push_back(MyString("Apple"));
		myDeque.push_back(MyString("Banana"));
		myDeque.push_back(MyString("Carrot"));
		myDeque.push_front(MyString("Ant"));
		myDeque.push_front(MyString("Apricot"));
		myDeque.insert(myDeque.begin() + 2, MyString("Avocado"));

		// Вывод содержимого deque
		std::cout << "Deque contents before erasing:" << std::endl;
		for (const auto& str : myDeque) {
			std::cout << str.get() << std::endl;
		}
		std::cout << std::endl;

		// Удаление элементов из deque, в которых строчки начинаются с 'A' или 'a'
		auto it = myDeque.begin();
		while (it != myDeque.end()) {
			if (it->get()[0] == 'A' || it->get()[0] == 'a') {
				it = myDeque.erase(it);
			}
			else {
				++it;
			}
		}

		// Вывод содержимого deque после удаления
		std::cout << "Deque contents after erasing:" << std::endl;
		for (const auto& str : myDeque) {
			std::cout << str.get() << std::endl;
		}

		return 0;
}