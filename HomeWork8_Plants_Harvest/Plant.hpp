#pragma once

#ifndef Plants_HPP
#define Plants_HPP

#include<string>
#include<ctime>
#include<cstdlib>

#include"Harvest.hpp"

/// \brief Глобальный массив цветов фруктов
std::string colors_fruits [5] = { "red", "green", "white", "yellow", "pink" };

/// \brief Глобальный массив цветов ягод
std::string colors_berries[3] = { "red", "dark red", "black" };

/// \brief Базовый абстрактный класс для создания объектов - растений
class Plant {
public:	
	/// <summary>
	/// Параметрический конструктор объекта "Растение"
	/// </summary>
	/// <param name="name">Имя растения</param>
	/// <param name="plant_size">Размер растения</param>
	/// <param name="color">Цвет растения</param>
	/// <param name="max">Максимальное кол-во плодов растения</param>
	Plant(std::string name, std::string plant_size, std::string color, int max) {
		this->name_ = name;
		this->plant_size_ = plant_size;
		this->color_ = color;
		this->size_ = max;
		this->darr_ = new Harvest * [size_]; // Выделяем память под массив указателей на объекты Harvest
	}		
	/// \brief Виртуальный дэструктор
	virtual ~Plant() {}
	/// <summary>
	/// Гэттэр размера растения
	/// </summary>
	/// <returns>Размер растения</returns>
	std::string Plant_size()const { return plant_size_; }
	/// <summary>
	/// Гэттер цвета растения
	/// </summary>
	/// <returns>Цвет растения</returns>
	std::string Color()const { return color_; }	
	int size()const { return size_; }	
	/// <summary>
	/// Гэттэр адреса начала массива плодов объекта
	/// </summary>
	/// <returns>Адресс начала массива плодов объекта</returns>	
	Harvest** begin()const { return darr_; }
	/// <summary>
	/// Гэттэр адреса конца массива плодов объекта
	/// </summary>
	/// <returns>Адресс конца массива плодов объекта</returns>	
	Harvest** end()const { return (darr_ + size_); }
	/// <summary>
	/// Гэттэр имени растения
	/// </summary>
	/// <returns>Имя растенния</returns>
	std::string Name()const { return name_; }	
	/// \brief Виртуальный метод базового абстрактного класса для создания плодов
	virtual Harvest* Create() = 0;		
	/*!
		\brief Дружественная функция для заполнения растения плодами
		\details Пока кол-во объектов класса Fruit меньше максимального кол-ва плодов растения, работает метод Create() по созданию объекта Fruit.
		Функция заполняет динамический массив указателей адресами созданных объектов Fruit с помощью виртуального метода Create()
	*/
	friend void Fill_in(Plant& obj) {
		while (Fruit::Counter() < std::size(obj)) {
			obj.darr_[Fruit::Counter() - 1] = obj.Create();
		}
	}
	/*!
		\brief Дружественная функция для чистки памяти
		\details Функция удаляет каждый плод у растения, освобождает память из под динамического массива плодов у растения.
		Все указатели переводятся на нейтральный статус
	*/
	friend void Clean_memory(Plant& obj) {		
		if (obj.darr_) {				
			/*for (int i = 0; i < std::size(obj); ++i) {
				obj.darr_[i]->~Harvest(); // Чистим каждый объект (плод) у растения
				obj.darr_[i] = nullptr; // Указатель на удалённый объект (плод) переводим в нейтральный статус
			}*/
			for (auto& e : obj) {
				e->~Harvest(); // Чистим каждый объект (плод) у растения
				e = nullptr; // Указатель на удалённый объект (плод) переводим в нейтральный статус			
			}
			delete[] obj.darr_;	// Удаляем массив плодов
			obj.darr_ = nullptr; // Указатель на массив удалённых плодов растения переводим в нейтральный статус
			std::cout << "\033[90mThe memory has been freed!\033[0m" << std::endl;
		}
	}	
private:
	std::string name_; // Имя растения
	std::string plant_size_; // Размер растения
	std::string color_; // Цвет
	int size_; // Максимальное кол-во плодов на растении		
	Harvest** darr_; // Указатель на динамический массив, хранищий max_plants адресов, в каждом из которых хранится плод Harvest
};

/// \brief Класс-наследник для создания конкретного объекта - дерева с фруктами
class Tree :public Plant {
public:
	/// <summary>
	/// Параметрический конструктор для создания конкретного обьета класса Tree (Дерево), являющегося наследником абстрактного базового класса Plant (Растение)
	/// </summary>
	/// <param name="name">Название дерева</param>
	/// <param name="plant_size">Максимальное количество фруктов на дереве</param>
	/// <param name="color">Цвет дерева</param>
	/// <param name="max_plants">Максимальное кол-во плодов на дереве</param>
	Tree(std::string name, std::string plant_size, std::string color, int max_plants) :Plant(name, plant_size, color, max_plants) {	
		this->name_harvest_ = name.substr(0, name.find(' ')); // Парсим строку для вычленения имени фрукта из названия дерева
	}
	/// \brief Дэструктор объета "Дерево"
	~Tree() {}
	/// <summary>
	/// Конкретная реализация виртуальной функции базового абстрактного класса Plant для создания плода - объекта класса Fruit (Фрукт)
	/// </summary>
	/// <returns>Возвращает адресс памяти, по которому хранится созданный объект Fruit</returns>
	Harvest* Create() override {		
		return new Fruit(name_harvest_, colors_fruits[rand() % 5], rand() % (400 - 115)+115);
	}	
private:	
	std::string name_harvest_; // Имя плода дерева
	std::string type_ = "Tree"; // Тип растения	
};

/// \brief Класс-наследник для создания конкретного объекта - кустарника с ягодами
class Bush :public Plant {
public:
	/// <summary>
	/// Параметрический конструктор для создания конкретного обьета класса Bush (Куст), являющегося наследником абстрактного базового класса Plant (Растение)
	/// </summary>
	/// <param name="name">Название кустарника</param>
	/// <param name="plant_size">Максимальное количество ягод на кустарнике</param>
	/// <param name="color">Цвет кустарника</param>
	/// <param name="max_plants"> Максимальное кол-во ягод на кустарнике</param>
	Bush(std::string name, std::string plant_size, std::string color, int max_plants) :Plant(name, plant_size, color, max_plants) {
		this->name_harvest_ = name.substr(0, name.find(' ')); // Парсим строку для вычленения имени ягоды из названия кустарника
	}
	/// \brief Дэструктор объета "Кустарник"
	~Bush() {}
	Harvest* Create() override {
		return new Berries(name_harvest_, colors_berries[rand()%3], rand() % (30 - 5) + 5);
	}
private:
	std::string name_harvest_; // Имя плода кустарника	
	std::string type_ = "Bush"; // Тип растения	
};

#endif // !Plants_HPP
