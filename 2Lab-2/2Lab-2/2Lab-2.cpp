#include <iostream>
#include "Product.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<std::string>composition1 = { "a", "б", "в" };
    Product product1("А", 100.0, 50, composition1);

    std::vector<std::string>composition2 = { "a", "м", "н" };
    Product product2("Б", 100.0, 30, composition2);

    std::cout << "=== Продукты ===" << std::endl;
    std::cout << "Продукт 1: " << std::endl;
    product1.Display();
    std::cout << std::endl;

    std::cout << "Продукт 2: " << std::endl;
    product2.Display();
    std::cout << std::endl;

    std::cout << "=== Демонстрация оператора + ===" << std::endl;
    Product product3 = product1 + product2;
    product3.Display();
    std::cout << std::endl;

    std::cout << "=== Демонстрация оператора - ===" << std::endl;
    Product product4 = product1 - product2;
    product4.Display();
    std::cout << std::endl;

    std::cout << "=== Демонстрация оператора присваивания ===" << std::endl;
    Product product5;
    product5 = product2;
    std::cout << "Продукт5 получил даные продукта2: " << std::endl;
    product5.Display();
    std::cout << std::endl;

    std::cout << "=== Оператор -= ===" << std::endl;
    Product product6;
    product6 = product1;
    std::cout << "Продукт6 получил даные продукта1: " << std::endl;
    product6.Display();
    std::cout << std::endl;
    product6 -= product2;
    std::cout << "Продукт6 после вычитания присваиванием: " << std::endl;
    product6.Display();
    std::cout << std::endl;

    return 0;
}