#pragma once

#ifndef Harvest_HPP
#define Harvest_HPP

#include<string>

/*!
	\brief Абстрактный класс для создания объектов - плодов
*/
class Harvest {
public:
	/// <summary>
	/// Параметрический конструктор объекта "Плод"
	/// </summary>
	/// <param name="name">название плода</param>
	/// <param name="color">цвет плода</param>
	/// <param name="weight">вес плода</param>
	Harvest(std::string name, std::string color, float weight) {
		this->name_ = name;
		this->color_ = color;
		this->weight_ = weight;
		++counter_;
	}	
	/*!
		\brief Дэструктор объекта класса "Плод"
		\details Необходим для корректной работы статического поля counter
	*/
	~Harvest() { --counter_; };
	/// <summary>
	/// Гэттэр названия плода
	/// </summary>
	/// <returns>Название плода</returns>
	std::string Name()const { return name_; }
	/// <summary>
	/// Гэттэр цвета плода
	/// </summary>
	/// <returns>Цвет плода</returns>
	std::string Color()const { return color_; }	
	/// <summary>
	/// Гэттэр массы плода
	/// </summary>
	/// <returns>массу плода</returns>
	float Weight()const { return weight_; }		
	/// <summary>
	/// Статический гэттэр кол-ва созданных объектов класса Harvest
	/// </summary>
	/// <returns>Кол-во созданных объектов класса</returns>
	static int Counter() { return counter_; }	
	/// <summary>
	/// Гэттэр порядкового номера объекта
	/// </summary>
	/// <returns>Порядковый номер объекта</returns>
	int Number() { return ++number_; }
private:
	std::string name_; // Название плода
	std::string color_; // Цвет плода
	float weight_; // Вес плода
	static int counter_; // Статический счётчик кол-ва созданных объектов класса Harvest
	int number_ = Harvest::Counter(); // Порядковый номер созданного объекта 
};

int Harvest::counter_{}; // Счётчик созданных объектов класса Harvest изначально инициализирован 0

/*!
	\brief Класс-наследник для создания объектов - конкретных фруктов
*/
class Fruit :public Harvest{
public:	
	Fruit(std::string name, std::string color, float weight) :Harvest(name, color, weight) {} 	
private:
	std::string type_ = "Fruit";		
};

/*!
	\brief Класс-наследник для создания объектов - конкретных ягод
*/
class Berries:public Harvest {
public:
	Berries(std::string name, std::string color, float weight) :Harvest(name, color, weight) {}
private:
	std::string type_ = "Berries";
};

#endif // !Harvest_HPP