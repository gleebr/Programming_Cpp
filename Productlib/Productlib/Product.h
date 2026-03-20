#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

struct Ingredient { // Структура Ингредиент
    std::string name;
    double volume;

    Ingredient();
    Ingredient(const std::string& name_, double volume_);
    Ingredient(const Ingredient& other);
    ~Ingredient();

    void Display() const;

    bool operator==(const Ingredient& other) const {
        return name == other.name;
    }
    bool operator<(const Ingredient& other) const {
        return name < other.name;
    }

};

class Commission { // Класс Комиссия

private:
    std::string address;
    std::vector<Ingredient> forbiddenIngredients;
    int inspectionDate;

public:
    Commission(); // Конструкторы и деструктор
    Commission(const std::string& address_, const std::vector<Ingredient>& forbiddenIngredients_, int inspectionDate_);
    Commission(const Commission& other);
    ~Commission();

    Commission& operator=(const Commission& other);

    void SetAddress(const std::string& address_) { address = address_; }
    void SetForbiddenIngredients(const std::vector<Ingredient>& forbiddenIngredients_) { forbiddenIngredients = forbiddenIngredients_; }
    void SetInspectionDate(int inspectionDate_) { inspectionDate = inspectionDate_; }

    std::string getAddress() const { return address; }
    std::vector<Ingredient> getForbiddenIngredients() const { return forbiddenIngredients; }
    int getInspectionDate() const { return inspectionDate; }

    void Display() const; // Методы
    void addForbiddenIngredient(const Ingredient& ingredient);
    bool check(const class Product& product) const;
};

class Product {
private: // Поля
    std::string name;
    std::string description;
    float price;
    int expirationDate;
    std::string place;
    std::vector<Ingredient> composition;

public:
    Product(); // Конструкторы
    Product(const std::string& name_, const std::string& description_, float price_, int expirationDate_,
        const std::string& place_, const std::vector<Ingredient>& composition_);
    Product(const Product& other);

    ~Product(); // Деструктор

    Product& operator=(const Product& other); // Оператор присваивания

    Product operator+(const Product& other) const; // Операторы
    Product operator-(const Product& other) const;
    Product& operator-=(const Product& other);

    void setPrice(float price_); // Сеттеры
    void setName(const std::string& name_) { name = name_; }
    void setDescription(const std::string& description_) { description = description_; }
    void setExpirationDate(int expirationDate_) { expirationDate = expirationDate_; }
    void setPlace(const std::string& place_) { place = place_; }
    void setComposition(const std::vector<Ingredient>& composition_) { composition = composition_; }

    std::string getName() const { return name; } // Геттеры
    std::string getDescription() const { return description; }
    float getPrice() const { return price; }
    int getExpirationDate() const { return expirationDate; }
    std::string getPlace() const { return place; }
    std::vector<Ingredient> getComposition() const { return composition; }

    void Display() const; // Методы
    void DisplayPlace() const;
    void DecreaseExpirationDate(int days);
    bool checkExpiration(int checkDate) const;

private:
    static std::vector<Ingredient> commonComposition(const std::vector<Ingredient>& v1, // Методы для работы с векторами
        const std::vector<Ingredient>& v2);
    static std::vector<Ingredient> removeCommon(const std::vector<Ingredient>& v1,
        const std::vector<Ingredient>& v2);
    static void removeCommon_(std::vector<Ingredient>& target, const std::vector<Ingredient>& toRemove);
    static bool shouldRemove(const Ingredient& item, const std::vector<Ingredient>& toRemove);
};