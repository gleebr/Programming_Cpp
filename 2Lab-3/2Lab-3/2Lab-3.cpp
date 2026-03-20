#include <iostream>
#include "Product.h"
#pragma comment(lib, "Productlib.lib")

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<Ingredient>composition1 = { Ingredient("сахар", 150.0), Ingredient("яйца", 2.0), Ingredient("масло", 200.0), Ingredient("мука", 500.0) };
    Product product1("Вафли", "Десерт", 400.0, 30, "Магазин: ...", composition1);

    std::vector<Ingredient> forbidden = {Ingredient("сахар", 100.0), Ingredient("соль", 0.0), Ingredient("консервант", 0.0)};
    Commission commission("Ул. Зелёная, 5", forbidden, 10);

    product1.Display();
    commission.Display();

    commission.check(product1);

    std::cout << "================================================================" << std::endl;

    std::vector<Ingredient>composition2 = { Ingredient("сахар", 50.0), Ingredient("яйца", 3.0),Ingredient("мука", 500.0) };
    Product product2("Блины", "Десерт", 200.0, 5, "Магазин: ...", composition2);

    product2.Display();
    commission.Display();

    commission.check(product2);

    Product product3 = product1 + product2;
    product3.Display();

    Product product4 = product1 - product2;
    product4.Display();

    product2 -= product1;
    product2.Display();


    return 0;
}