#include <iostream>

void Answer(float a) {
	std::cout << "Используется функция вывода ответа (для 1-го числа)" << std::endl;
	std::cout << "Обратное значение числа: " << 1 / a << std::endl;
}

void Answer(float a, float b) {
	std::cout << "Используется функция вывода ответа (для 2-х чисел)" << std::endl;
	std::cout << "Значение выражения: " << a * a + 2 * a * b + b * b << std::endl;
}

void Search(float a, float b) {
	std::cout << "Используется функция анализа введённых данных и нахождения для них ответа" << std::endl;
	if (a != 0 && b != 0) {
		Answer(a, b);
	}
	else if (a == 0 && b != 0) {
		Answer(b);
	}
	else if (a != 0 && b == 0) {
		Answer(a);
	}
	else if (a == 0 && b == 0) {
		std::cout << "Ответ не может быть дан, так как оба числа равны нулю" << std::endl;
	}
}

void Lab1(float x, float y) {
	std::cout << "Используется функция расчёта и вывода середины интервала, " << std::endl;
	double TheMiddle = (x + y) / 2;
	std::cout << "Середина интервала равна " << TheMiddle << std::endl;

	float LowerLimitForFloat = std::numeric_limits<float>::min();
	float UpperLimitForFloat = std::numeric_limits<float>::max();

	double LowerLimitForDouble = std::numeric_limits<double>::min();
	double UpperLimitForDouble = std::numeric_limits<double>::max();

	std::cout << "float занимает " << sizeof(float) * 8 << " бита и принимает значения в диапазоне " << LowerLimitForFloat << " - " << UpperLimitForFloat << std::endl;
	std::cout << "double занимает " << sizeof(double) * 8 << " бита и принимает значения в диапазоне " << LowerLimitForDouble << " - " << UpperLimitForDouble << std::endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	
	int n;
	float a, b, TheFirstNumber, TheSecondNumber;
	std::cout << "Какой пункт выбрать для выполнения (1 или 2): " << std::endl;
	std::cin >> n;

	if (n == 1) {
		std::cout << "Введите 2 целых числа (0 не считается за число): " << std::endl;
		std::cin >> a >> b;
		Search(a, b);
	}
	else if (n == 2) {
		std::cout << "Введите значения на действительной оси (2 числа):" << std::endl;
		std::cin >> TheFirstNumber >> TheSecondNumber;
		Lab1(TheFirstNumber, TheSecondNumber);
	}
	else {
		std::cout << "Нет такого пункта" << std::endl;
	}
	return 0;
}
