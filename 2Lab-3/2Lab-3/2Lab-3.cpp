#include <iostream>
#include "Product.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<Ingredient>composition1 = { Ingredient("сахар", 150.0), Ingredient("яйца", 2.0), Ingredient("масло", 200.0), Ingredient("мука", 500.0) };
    Product product("Вафли", "Десерт", 400.0, 30, "Магазин: ...", composition1);

    std::vector<std::string>forbidden = { "консервант", "сахар" };
    Commission commission("Ул. Зелёная, 5", forbidden, 10);

    product.Display();
    commission.Display();

    commission.check(product);

    return 0;
}