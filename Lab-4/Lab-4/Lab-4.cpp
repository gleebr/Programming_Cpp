#include <iostream>

int main()
{
    // Задание 1
    setlocale(LC_ALL, "Russian");

    const int N = 8;
    int arr[N];
    int count = 0;

    std::cout << "Введите данные для массива: " << std::endl;
    for (int i = 0; i < N; ++i) // Заполнение массива
    {
        std::cin >> arr[i];
        if (arr[i] == 25) // Подсчёт кол-ва чисел 25
        {
            count += 1;
        }
    }

    if (count > 2) // Упорядочивание массива по возрастанию в случае выполнения условия
    {
        for (int i = 0; i < N - 1; ++i)
        {
            for (int j = i + 1; j < N; ++j)
            {
                if (arr[i] > arr[j])
                {
                    std::swap(arr[i], arr[j]);
                }
            }
        }

        std::cout << "Полученный массив: " << std::endl; // Вывод нового массива
        for (int i = 0; i < N; ++i)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Число 25 не встречается больше двух раз в данном массиве" << std::endl;
    }

    // Задание 2
    const int NMat = 3, MMat = 4;
    int Mat[NMat][MMat]; // Создание матрицы

    std::cout << "Введите данные для матрицы: " << std::endl;
    for (int i = 0; i < NMat; ++i) // Заполнение матрицы
    {
        for (int j = 0; j < MMat; ++j)
        {
            std::cin >> Mat[i][j];
        }
    }

    int MaxCount = 0;
    int MaxN = 0;
    for (int i = 0; i < NMat; ++i) // Поиск строки с наибольшим количеством нулей
    {
        int count_0 = 0;
        for (int j = 0; j < MMat; ++j)
        {
            if (Mat[i][j] == 0)
            {
                count_0 += 1;
            }
        }
        if (count_0 > MaxCount)
        {
            MaxCount = count_0;
            MaxN = i;
        }
    }

    if (MaxCount > 0) // Замена нулей в найденной строке на 888
    {
        for (int j = 0; j < MMat; ++j)
        {
            if (Mat[MaxN][j] == 0)
            {
                Mat[MaxN][j] = 888;
            }
        }
    
        std::cout << "Полученная матрица: " << std::endl; // Вывод полученной матрицы
        for (int i = 0; i < NMat; ++i)
        {
            for (int j = 0; j < MMat; ++j)
            {
                std::cout << Mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "В матрице нет нулей" << std::endl;
    }
    
    return 0;
}