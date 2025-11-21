#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    // Задание 1

    int N;
    int Num = 0;
    double Sum = 0, MinA = 15;
    std::cout << "Количество чисел в последовательности: " << std::endl; // Ввод количества чисел в последовательности
    std::cin >> N;
    if (N != 0)
    {
        std::cout << "Числа последовательности: " << std::endl;
        for (int i = 1; i <= N; ++i) // Ввод чисел последовательности
        {
            double A;
            std::cin >> A;

            if (A <= 10.12) // нахождение суммы всех чисел, не превышающих 10.12, наименьшего из них и его номера в последовательности
            {
                Sum += A;
                if (A < MinA)
                {
                    MinA = A;
                    Num = i;
                }
            }
        }
        if (Sum == 0)
        {
            std::cout << "Подходящие значения не найдены " << std::endl;
        }
        else // Вывод полученых данных
        {
            std::cout << "Сумма всех чисел, удовлетворяющих условию: " << Sum << std::endl;
            std::cout << "Наименьшее из чисел в последовательности: " << MinA << std::endl;
            std::cout << "Номер наименьшего элемента в последовательности: " << Num << std::endl;
        }
    }
    else
    {
        std::cout << "Задана пустая последовательность " << std::endl;
    }

    // Задание 2

    int x;

    do
    {
        std::cout << "Введите число x (по модулю меньше 1000): " << std::endl; // Введение числа x
        std::cin >> x;

        if (abs(x) >= 1000) // Проверка корректности числа x
        {
            std::cout << "Введено некорректное значение x " << std::endl;
        }
    } while (abs(x) >= 1000);

    int abs_x = abs(x);
    int Index = -1;
    int AnsIndex = 0;

    do // Нахождение индекса последней цифры 3 в записи числа x
    {
        Index += 1;
        if (abs_x % 10 == 3)
        {
            AnsIndex = Index;
            break;
        }
        abs_x /= 10;
    } while (abs_x);

    if (Index != -1) // Вывод индекса последней цифры 3
    {
        std::cout << "Индекс последней цифры 3: " << AnsIndex << std::endl;
    }
    else
    {
        std::cout << "Цифры 3 в составе числа нет " << std::endl;
    }

}