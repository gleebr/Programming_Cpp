#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>

class Product {
private: // Поля
    std::string name;
    float price;
    int expirationDate;
    std::vector<std::string> composition; // Вектор состава

public:
    Product(); // Конструкторы
    Product(const std::string& name, float price, int expirationDate,
        const std::vector<std::string>& composition);
    Product(const Product& other);

    ~Product(); // Деструктор

    Product& operator=(const Product& other); // Оператор присваивания

    Product operator+(const Product& other) const; // Операторы
    Product operator-(const Product& other) const;
    Product& operator-=(const Product& other);

    void setPrice(float price_); // Сеттеры
    void setName(const std::string& name_) { name = name_; }
    void setExpirationDate(int expirationDate_) { expirationDate = expirationDate_; }
    void setComposition(const std::vector<std::string>& composition_) { composition = composition_; }

    std::string getName() const { return name; } // Геттеры
    float getPrice() const { return price; }
    int getExpirationDate() const { return expirationDate; }
    std::vector<std::string> getComposition() const { return composition; }

    void Display() const; // Методы
    void DecreaseExpirationDate();

private:
    static std::vector<std::string> commonComposition(const std::vector<std::string>& v1, // Методы для работы с векторами
        const std::vector<std::string>& v2);
    static std::vector<std::string> removeCommon(const std::vector<std::string>& v1,
        const std::vector<std::string>& v2);
    static void removeCommon_(std::vector<std::string>& target, const std::vector<std::string>& toRemove);
    static bool shouldRemove(const std::string& item, const std::vector<std::string>& toRemove);
};