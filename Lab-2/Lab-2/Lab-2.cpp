#include <iostream>
#include <bitset>

int main()
{
	setlocale(LC_ALL, "Russian");

	unsigned short A;
	int i;
	std::cout << "Введите значения для A и i: " << std::endl;
	std::cin >> A >> i;
	A = abs(A);

	if (i < 0 || i > 15) // проверка на правильность значения i-го бита
	{
		std::cout << "Введено неправильное значение i!" << std::endl;
		return 0;
	}

	std::bitset <16> BinA = A;
	std::cout << A << " - " << BinA << std::endl; // отладочный вывод для A

	bool bit_i = (A >> i) & 1;
	if (bit_i == 0)
	{
		bool bit_0 = A & 1;
		A = (A & ~(1 << i)) | (bit_0 << i); // изменение бита i
		unsigned short NewA = (A & ~1) | (bit_i); // изменение 0-го бита
		std::bitset <16> NewBinA = NewA;
		std::cout << "A после преобразований - " << NewBinA << std::endl;
	}
	else
	{
		unsigned int Num1, Num2, Num3;
		std::cout << "Введите три целых числа: " << std::endl;
		std::cin >> Num1 >> Num2 >> Num3;
		int NewNum1 = labs(Num1);
		int NewNum2 = labs(Num2);
		int NewNum3 = labs(Num3);

		if (NewNum1 == NewNum2 || NewNum2 == NewNum3 || NewNum1 == NewNum3)
		{
			std::cout << "Код 0. Вычисление невозможно" << std::endl;
		}
		else
		{
			int Mid = (NewNum1 > NewNum2) ? // введение тернарного оператора для вычисления среднего числа по модулю
				((NewNum1 < NewNum3) ? NewNum1 : ((NewNum2 > NewNum3) ? NewNum2 : NewNum3)) :
				((NewNum2 < NewNum3) ? NewNum2 : ((NewNum1 > NewNum3) ? NewNum1 : NewNum3));
			std::cout << "Среднее число по модулю: " << Mid << std::endl;
		}
	}

	int RegionNumber; // обработка региона
	std::cout << "Введите номер региона: " << std::endl;
	std::cin >> RegionNumber;
	switch (RegionNumber)
	{
	case 102:
		std::cout << "Республика Башкортостан" << std::endl;
		break;
	case 11:
		std::cout << "Республика Коми" << std::endl;
		break;
	case 13:
		std::cout << "Республика Мордовия" << std::endl;
		break;
	case 15:
		std::cout << "Республика Северная Осетия - Алания" << std::endl;
		break;
	case 116:
		case 716:
			std::cout << "Республика Татарстан" << std::endl;
			break;
		break;
	default:
		std::cout << "Информация временно недоступна" << std::endl;
	}
	return 0;
}