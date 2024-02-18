# include <iostream>
#include<string>
#include"Plant.hpp"
#include"Harvest.hpp"

/*!
	\brief Функция для вывода в консоль информации о плодах растения
	\details Функция реализует цикл range base for.
	Методы begin() и end() для работы цикла range bose for прописаны в базовом абстрактном классе Plant 
*/
void Print(Plant const& obj);

int main() {	
	//------------------ Создание и удаление яблони --------------------
	std::cout << "\033[91mStep 1 - Creating and deleting an apple tree\033[0m" << std::endl;
	Tree A("apple tree", "big", "green", 25); // Конкретный наследник базового класса Plants - яблоня 
	srand(time(NULL));
	Fill_in(A); // Заполняем растение плодами
	Print(A); // Выводим результат в консоль
	system("pause");
	system("cls");	
	Clean_memory(A); // Чистим память
	A.~Tree(); // Удаляем растение	
	//------------------ Создание и удаление груши --------------------
	std::cout << std::endl << "\033[91mStep 2 - Creating and deleting a pear tree\033[0m" << std::endl;
	Tree P("pear tree", "medium", "yellow", 15);
	Fill_in(P);
	Print(P);
	system("pause");
	system("cls");
	Clean_memory(P);
	P.~Tree();
	//------------------ Создание и удаление вишни --------------------
	std::cout << std::endl << "\033[91mStep 3 - Creating and deleting a cherry bush\033[0m" << std::endl;
	Bush C("cherry bush", "big", "dark green", 50);
	Fill_in(C);
	Print(C);
	system("pause");
	system("cls");
	Clean_memory(C);
	C.~Bush();
	//------------------ Создание и удаление ежевики --------------------
	std::cout << std::endl << "\033[91mStep 4 - Creating and deleting a blackberry bush\033[0m" << std::endl;
	Bush B("blackberry bush", "small", "black", 10);
	Fill_in(B);
	Print(B);
	system("pause");
	system("cls");
	Clean_memory(B);
	B.~Bush();

	return 0;
}

void Print(Plant const& obj) {
	std::cout << "\033[93mA " << obj.Plant_size() << ' ' << obj.Color() << ' ' << obj.Name() << " contains the following harvest (there are "<< Harvest::Counter() <<" harvests):\033[0m" << std::endl;		
	for (auto& e : obj)
		std::cout << e->Number() << ". " << e->Color() << ' ' << e->Name() << " weighing " << e->Weight() << " grams" << std::endl;
	std::cout << std::endl;
}
