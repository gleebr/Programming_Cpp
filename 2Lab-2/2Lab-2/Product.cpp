#include "Product.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <functional>

Product::Product() : name(""), price(0.0), expirationDate(0),composition() {} // Конструктор по умолчанию

Product::Product(const std::string& name, // Конструктор полного заполнения
    float price, int expirationDate, const std::vector<std::string>& composition)
    : name(name), price(price), expirationDate(expirationDate), composition(composition) {
    setPrice(price);
}

Product::Product(const Product& other) : name(other.name), price(other.price), // Конструктор копирования 
    expirationDate(other.expirationDate), composition(other.composition) {}

Product::~Product() { // Деструктор
    composition.clear(); // Очистка вектора
    composition.shrink_to_fit();
    std::cout << "Деструктор класса Product запущен" << std::endl;
}

Product& Product::operator=(const Product& other) { // Оператор присваивания
    if (this != &other) {
        name = other.name;
        price = other.price;
        expirationDate = other.expirationDate;
        composition = other.composition;
    }
    return *this;
}

Product Product::operator+(const Product& other) const { // Оператор +
    Product result;

    result.name = "Смесь " + this->name + " и " + other.name;
    result.price = (this->price + other.price) * 0.9;
    result.expirationDate = std::min(this->expirationDate, other.expirationDate);
    result.composition = commonComposition(this->composition, other.composition);
    return result;
}

Product Product::operator-(const Product& other) const { // Оператор -
    Product result;

    result.name = "Выбор " + this->name + " без " + other.name;
    result.price = this->price * 0.9;
    result.expirationDate = std::max(0, this->expirationDate - 2);
    result.composition = removeCommon(this->composition, other.composition);
    result.composition.push_back("консервант Т1000");
    return result;
}

Product& Product::operator-=(const Product& other) { // Оператор -=
    this->name = "Выбор " + this->name + " без " + other.name;
    this->price = this->price * 0.9;
    this->expirationDate = std::max(0, this->expirationDate - 2);
    removeCommon_(this->composition, other.composition);
    this->composition.push_back("консервант Т1000");
    for (const auto& item : this->composition) std::cout << item << " ";
    std::cout << std::endl;
    return *this;
}

void Product::setPrice(float price_) { // Сеттер для цены
    if (price_ >= 0) {
        price = price_;
    }
    else {
        throw std::invalid_argument("Цена не может быть отрицательной");
    }
}

void Product::Display() const { // Вывод всей информации
    std::cout << "Название товара: " << name << std::endl;
    std::cout << "Цена товара: " << price << " руб" << std::endl;
    std::cout << "Срок годности товара: " << expirationDate << " дней" << std::endl;
    std::cout << "Состав товара: ";
    if (composition.empty()) {
        std::cout << "не был указан" << std::endl;
    }
    else {
        for (size_t i = 0; i < composition.size(); ++i) {
            std::cout << composition[i];
            if (i < composition.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

void Product::DecreaseExpirationDate() { // Уменьшение срока хранения на 1 день
    std::cout << "Уменьшение срока хранения на 1 день:" << std::endl;
    if (expirationDate > 0) {
        expirationDate--;
    }
    else {
        std::cout << "Срок годности товара уже истек" << std::endl;
    }
}

// Функция для написания общего состава без повторов
std::vector<std::string> Product::commonComposition(const std::vector<std::string>& v1, const std::vector<std::string>& v2) {
    std::vector<std::string> result;
    for (const auto& item : v1) {
        if (std::find(result.begin(), result.end(), item) == result.end()) {
            result.push_back(item);
        }
    }
    for (const auto& item : v2) {
        if (std::find(result.begin(), result.end(), item) == result.end()) {
            result.push_back(item);
        }
    }
    return result;
}

// Функция для написания состава1 без состава2
std::vector<std::string> Product::removeCommon(const std::vector<std::string>& v1, const std::vector<std::string>& v2) {
    std::vector<std::string> result;
    for (const auto& item : v1) {
        if (std::find(v2.begin(), v2.end(), item) == v2.end()) {
            result.push_back(item);
        }
    }
    return result;
}

// Отдельные функции для оператора -=
bool Product::shouldRemove(const std::string& item, const std::vector<std::string>& toRemove) {
    return std::find(toRemove.begin(), toRemove.end(), item) != toRemove.end();
}
void Product::removeCommon_(std::vector<std::string>& target, const std::vector<std::string>& toRemove) {
    auto it = std::remove_if(target.begin(), target.end(), std::bind(shouldRemove, std::placeholders::_1, toRemove));
    target.erase(it, target.end());
}
