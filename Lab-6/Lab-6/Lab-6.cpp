#include <iostream>

int* FindColumns(int** Matrix, int M, int N, int& count) { // Функция для поиска столбцов с 0-ми значениями
    int* ZeroColumns = NULL;
    count = 0;

    for (int j = 0; j < N; ++j) {
        bool Check = false;
        for (int i = 0; i < M; ++i) {
            if (Matrix[i][j] == 0) {
                Check = true;
                break;
            }
        }
        if (Check) {
            ZeroColumns = (int*)realloc(ZeroColumns, (count + 1) * sizeof(int));
            ZeroColumns[count] = j;
            count += 1;
        }
    }
    
    return ZeroColumns;
}

void Remove(int*** Matrix, int M, int* N, int* Columns, int count) { // Функция для удаления столбцов из матрицы
    if (count == 0) { // Оставление матрицы без изменений в случае отсутствия столбцов с 0-ми значениями
        return;
    }

    int LastN = *N - count;

    for (int i = 0; i < M; ++i) {
        int j1 = 0;

        for (int j = 0; j < *N; ++j) { // В итоговую матрицу попадают только столбцы без нулей
            bool CheckRemove = false;
            for (int c = 0; c < count; ++c) {
                if (j == Columns[c]) {
                    CheckRemove = true;
                    break;
                }
            }
            if (!CheckRemove) {
                if (j1 != j) {
                    (*Matrix)[i][j1] = (*Matrix)[i][j];
                }
                j1 += 1;
            }
        }

        (*Matrix)[i] = (int*)realloc((*Matrix)[i], LastN * sizeof(int));
    }
    *N = LastN;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    std::cout << "Пункт 1" << std::endl;

    int** Matrix = (int**)malloc(2 * sizeof(int*)); // Создание двумерного динамического массива формата 2*2

    for (int i = 0; i < 2; ++i) {
        Matrix[i] = (int*)malloc(2 * sizeof(int));
    }
    
    int A, B, C, D;

    do {
        std::cout << "Введите значение для A (A не может быть отрицательным): " << std::endl; // Ввод элементов матрицы
        std::cin >> A;
        if (A < 0) {
            std::cout << "Ошибка, введите корректное значение для A" << std::endl;
        }
    } while (A < 0);

    do {
        std::cout << "Введите значение для B (B не может быть отрицательным): " << std::endl;
        std::cin >> B;
        if (B < 0) {
            std::cout << "Ошибка, введите корректное значение для B" << std::endl;
        }
    } while (B < 0);

    std::cout << "Введите значение для C: " << std::endl;
    std::cin >> C;
    std::cout << "Введите значение для D: " << std::endl;
    std::cin >> D;

    Matrix[0][0] = A;
    Matrix[0][1] = B;
    Matrix[1][0] = C;
    Matrix[1][1] = D;

    std::cout << "Начальная матрица: " << std::endl; // Вывод начальной матрицы
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << Matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    int M = 2 + A;
    int N = 2 + B;

    Matrix = (int**)realloc(Matrix, M * sizeof(int*)); // Преобразование начальной матрицы
    for (int i = 2; i < M; ++i) {
        Matrix[i] = (int*)malloc(N * sizeof(int));
    }

    for (int i = 0; i < M; ++i) {
        if (i < 2) {
            Matrix[i] = (int*)realloc(Matrix[i], N * sizeof(int));
        }
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(i < 2 && j < 2)) {
                if (i == 0 && j >= 2) {
                    Matrix[i][j] = -1 * C + (j - 1) * D;
                }
                else if (i == 1 && j >= 2) {
                    Matrix[i][j] = 0 * C + (j - 1) * D;
                }
                else if (i >= 2) {
                    if (j == 0) {
                        Matrix[i][j] = (i - 1) * C - 1 * D;
                    }
                    else if (j == 1) {
                        Matrix[i][j] = (i - 1) * C + 0 * D;
                    }
                    else {
                        Matrix[i][j] = (i - 1) * C + (j - 1) * D;
                    }
                }
            }
        }
    }

    std::cout << "Преобразованная матрица: " << std::endl; // Вывод преобразованной матрицы
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << Matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    int count;
    int* Columns = FindColumns(Matrix, M, N, count); // Поиск столбцов с нулями через функцию

    std::cout << "Нули содержат столбцы под следующими номерами: " << std::endl; // Вывод столбцов, которые соержат нули
    if (count == 0) {
        std::cout << " - " << std::endl;
    }
    else {
        for (int i = 0; i < count; ++i) {
            std::cout << Columns[i] << " ";
        }
    }
    std::cout << std::endl;

    if (count > 0) { // Финальное изменение матрицы через функцию
        Remove(&Matrix, M, &N, Columns, count);
    }

    std::cout << "Полученная матрица: " << std::endl; // Вывод финальной матрицы
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << Matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < M; ++i) {
        free(Matrix[i]);
    }
    free(Matrix);
    
    free(Columns);
    
    std::cout << "Пункт 2" << std::endl;

    float a, b; // Введение 2-х вещественных переменных

    std::cout << "Введите значение переменной a: " << std::endl;
    std::cin >> a;

    std::cout << "Введите значение переменной b: " << std::endl;
    std::cin >> b;

    float* ptrA = new float(a); // Направление указателей на переменные a и b
    float* ptrB = new float(b);
    
    *ptrA *= 3; // Увеличение a в 3 раза  и вывод промежуточных значений
    std::cout << "Новое значение a: " << *ptrA << ". Переменная b: " << *ptrB << std::endl;
    
    float temp = *ptrA; // Перемена мест значений переменных
    *ptrA = *ptrB;
    *ptrB = temp;

    a = *ptrA; // Обновление переменных (привеление к финальному виду)
    b = *ptrB;

    std::cout << "Переменные a и b после преобразований: " << std::endl;
    std::cout << "a = " << a << "; b = " << b << std::endl;

    return 0;
}