#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <ctime>
#include <algorithm>

void Menu() { // Консольное меню для информирования пользователя
    std::cout << "Меню команд:" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "1. Просмотр массива" << std::endl;
    std::cout << "2. Добавить элемент в начало" << std::endl;
    std::cout << "3. Добавить элемент в конец" << std::endl;
    std::cout << "4. Очистка всего массива" << std::endl;
    std::cout << "5. Поиск элемента в массиве" << std::endl;
    std::cout << "6. Задание" << std::endl;
}

void View(const std::vector <int>& arr) { // Функция для просмотра массива
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i < arr.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

void AddToBeginning(std::vector <int>& arr, int element) { // Функция для добавления элемента в начало массива
    arr.insert(arr.begin(), element);
}

void AddToEnd(std::vector <int>& arr, int element) { // Функция для добавления элемента в конец массива
    arr.push_back(element);
}

void Clear(std::vector <int>& arr) { // Функция для очистки массива
    arr.clear();
}

std::vector <size_t> Search(const std::vector <int>& arr, int element) { // Функция для поиска индексов элементов
    std::vector <size_t> index;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == element) {
            index.push_back(i);
        }
    }
    return index;
}

void DisplaySearch(const std::vector <size_t>& index) { // Функция для вывода результатов поиска
    if (index.size() == 0) {
        std::cout << "[]" << std::endl;
    }
    else {
        std::cout << "[";
        for (size_t i = 0; i < index.size(); ++i) {
            std::cout << index[i];
            if (i < index.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
}

void Task(std::vector <int>& arr, int K) { // Функция для выполнения задания 5 варианта
    std::cout << "Начальный вид массива: " << std::endl;
    View(arr);

    int sum = 0;
    std::vector <int> sequence;

    for (int i = 1; sum < K; ++i) {
        sum += i;
        sequence.push_back(i);

        if (sum == K) {
            for (size_t i = 0; i < sequence.size(); ++i) {
                int n = sequence[i];
                AddToEnd(arr, n);
            }
            std::cout << "Была добавлена последовательность: " << std::endl;
            View(sequence);
            std::cout << "Новый вид массива: " << std::endl;
            View(arr);
            return;
        }
    }

    std::vector <int> temp = arr;
    arr.clear();
    for (size_t i = 0; i < temp.size(); ++i) {
        arr.push_back(temp[i]);
        if (i % 2 == 0) {
            arr.push_back(temp[i]);
        }
    }
    std::cout << "Было произведено дублирование чисел на чётных позициях" << std::endl;
    std::cout << "Новый вид массива: " << std::endl;
    View(arr);
}

const size_t ArraySize = 10;
const int MinElement = -10;
const int MaxElement = 10;

int RandomNumber() { // Функция для генерации случайного числа
    return rand() % (MaxElement - MinElement + 1) + MinElement;
}

void Display2(const std::array <int, ArraySize>& arr2) { // Функция для отображения массива
    std::cout << "[";
    for (size_t i = 0; i < arr2.size(); ++i) {
        std::cout << arr2[i];
        if (i < arr2.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

// Функции сортировки с разными способами передачи аргументов

void SortByValue(std::array <int, ArraySize> arr2, bool order) { // Передача по значению
    std::cout << "Массив до сортировки с помощью передачи аргумента в функцию по значению: ";
    Display2(arr2);

    if (order) {
        std::sort(arr2.begin(), arr2.end());
    }
    else {
        std::sort(arr2.begin(), arr2.end(), std::greater<int>());
    }

    std::cout << "Массив после сортировки с помощью передачи аргумента в функцию по значению: ";
    Display2(arr2);
}

void SortByReference(std::array <int, ArraySize>& arr2, bool order) { // Передача по ссылке
    std::cout << "Массив до сортировки с помощью передачи аргумента в функцию по ссылке: ";
    Display2(arr2);

    if (order) {
        std::sort(arr2.begin(), arr2.end());
    }
    else {
        std::sort(arr2.begin(), arr2.end(), std::greater<int>());
    }

    std::cout << "Массив после сортировки с помощью передачи аргумента в функцию по ссылке: ";
    Display2(arr2);
}

void SortByPointer(std::array <int, ArraySize>* arrPtr, bool order) { // Передача по указателю
    if (arrPtr == nullptr) {
        std::cout << "Ошибка. Нулевой указатель" << std::endl;
        return;
    }

    std::cout << "Массив до сортировки с помощью передачи аргумента в функцию по указателю: ";
    Display2(*arrPtr);

    if (order) {
        std::sort(arrPtr->begin(), arrPtr->end());
    }
    else {
        std::sort(arrPtr->begin(), arrPtr->end(), std::greater<int>());
    }

    std::cout << "Массив после сортировки с помощью передачи аргумента в функцию по указателю: ";
    Display2(*arrPtr);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Пункт 1" << std::endl;
    std::cout << "Выбран std::vector" << std::endl;

    std::vector <int> arr;
    int choice;
    Menu();

    do {
        std::cout << "Выберите действие: " << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 0:
            std::cout << "Выход..." << std::endl;
            break;
        case 1:
            std::cout << "Просмотр массива: " << std::endl;
            View(arr);
            break;
        case 2: {
            std::cout << "Добавление элемента в начало массива: " << std::endl;
            int element;
            std::cin >> element;
            AddToBeginning(arr, element);
            break;
        }
        case 3: {
            std::cout << "Добавление элемента в конец массива: " << std::endl;
            int element;
            std::cin >> element;
            AddToEnd(arr, element);
            break;
        }
        case 4:
            std::cout << "Очитка массива..." << std::endl;
            Clear(arr);
            break;
        case 5: {
            std::cout << "Поиск элемента в массиве: " << std::endl;
            int element;
            std::cin >> element;
            std::vector <size_t> index = Search(arr, element);
            DisplaySearch(index);
            break;
        }
        case 6: {
            int K;
            std::cout << "Выполнение задания... Введите положительное число K: " << std::endl;
            std::cin >> K;
            if (K <= 0) {
                std::cout << "K не соответствует условию!" << std::endl;
                break;
            }
            Task(arr, K);
            break;
        }
        default:
            std::cout << "Такого пункта нет!" << std::endl;
            break;
        }
    } while (choice != 0);

    std::cout << "Пункт 2" << std::endl;
    std::cout << "Выбран std::array" << std::endl;

    srand(static_cast<unsigned>(time(0)));

    std::array <int, ArraySize> arr2;
    for (size_t i = 0; i < ArraySize; ++i) {
        arr2[i] = RandomNumber();
    }

    std::array <int, ArraySize> original_arr2 = arr2;

    std::cout << "Оригинальный массив: " << std::endl;
    Display2(arr2);

    // Демонстрация разных способов сортировки массивов
    
    std::cout << "1. Выполняется передача аргументов массива в функцию по значению. \nОсобенность: создаётся полная копия массива, поэтому изменения внутри функции не затрагивают оригинальный массив; \nиз-за лишнего копирования неэффективно для больших массивов" << std::endl;
    std::cout << "Выполнение сортировки по возрастанию..." << std::endl;
    SortByValue(arr2, true); // Сортировка по возрастанию
    std::cout << "Выполнение сортировки по убыванию..." << std::endl;
    SortByValue(arr2, false); //Сортировка по убыванию
    std::cout << "Оригинальный массив после вызова функции: ";
    Display2(arr2);
    std::cout << "Оригинальный массив не изменился" << std::endl;

    std::cout << "" << std::endl;

    std::cout << "2. Выполняется передача аргументов массива в функцию по ссылке. \nОсобенность: работа идёт в оригинальном массиве, он изменяется внутри функции, т.к. на него передаётся ссылка; \nиз-за отсутствия лишнего копирования эффективно для больших массивов" << std::endl;
    std::cout << "Выполнение сортировки по возрастанию..." << std::endl;
    SortByReference(arr2, true); // Сортировка по возрастанию
    std::cout << "Выполнение сортировки по убыванию..." << std::endl;
    SortByReference(arr2, false); //Сортировка по убыванию
    std::cout << "Оригинальный массив после вызова функции: ";
    Display2(arr2);
    std::cout << "Оригинальный массив изменился" << std::endl;

    std::cout << "" << std::endl;

    arr2 = original_arr2;
    std::cout << "3. Выполняется передача аргументов массива в функцию по указателю. \nОсобенность: передаётся указатель на первый элемент массива, поэтому функция меняется; \nнеобходима проверка на nullptr" << std::endl;
    std::cout << "Выполнение сортировки по возрастанию..." << std::endl;
    SortByReference(arr2, true); // Сортировка по возрастанию
    std::cout << "Выполнение сортировки по убыванию..." << std::endl;
    SortByReference(arr2, false); //Сортировка по убыванию
    std::cout << "Оригинальный массив после вызова функции: ";
    Display2(arr2);
    std::cout << "Оригинальный массив изменился" << std::endl;
    
    std::cout << "" << std::endl;
    std::cout << "В задании нет выбора, т.к. array имеет фиксированный размер, \nпоэтому с ним нельзя добавлять элементы в начало и конец массива в п1, как с vector. \nVector и array могут играть одну роль в тех случаях, когда не требуется изменять размер массива, как в п2" << std::endl;

    return 0;
}