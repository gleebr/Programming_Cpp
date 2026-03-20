#include <iostream>
#include "Product.h"
#pragma comment(lib, "Productlib.lib")

int main()
{
	setlocale(LC_ALL, "Russian");
	float TheFirstNumber;
	float TheSecondNumber;

	/*
	Выбран тип данных float, т.к.в задании говорится про действительную ось
	(поэтому могут использоваться вещественные числа)
	*/

	std::cout << "Введите значения на действительной оси (2 числа):" << std::endl;
	std::cin >> TheFirstNumber >> TheSecondNumber;

	double TheMiddle = (TheFirstNumber + TheSecondNumber) / 2; // double, т.к. результат может быть вещественным числом, большим, чем float
	std::cout << "Середина интервала равна " << TheMiddle << std::endl;

	std::cout << "Типы данных" << std::endl;
	float LowerLimitForFloat = std::numeric_limits<float>::min(); // float, т.к. результат может быть вещественным числом
	float UpperLimitForFloat = std::numeric_limits<float>::max(); // аналогично

	double LowerLimitForDouble = std::numeric_limits<double>::min(); // double, т.к. результат может быть вещественным числом и может вмещать значение, равно значению double
	double UpperLimitForDouble = std::numeric_limits<double>::max(); // аналогично

	std::cout << "float занимает " << sizeof(float) * 8 << " бита и принимает значения в диапазоне " << LowerLimitForFloat << " - " << UpperLimitForFloat << std::endl;
	std::cout << "double занимает " << sizeof(double) * 8 << " бита и принимает значения в диапазоне " << LowerLimitForDouble << " - " << UpperLimitForDouble << std::endl;

	std::vector<Ingredient>composition1 = { Ingredient("сахар", 150.0), Ingredient("яйца", 2.0), Ingredient("масло", 200.0), Ingredient("мука", 500.0) };
	Product product1("Вафли", "Десерт", 400.0, 30, "Магазин: ...", composition1);

	std::vector<Ingredient> forbidden = {Ingredient("сахар", 100.0), Ingredient("соль", 0.0), Ingredient("консервант", 0.0)};
	Commission commission("Ул. Зелёная, 5", forbidden, 10);

	product1.Display();
	commission.Display();

	return 0;
}