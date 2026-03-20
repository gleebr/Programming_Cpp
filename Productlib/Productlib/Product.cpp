#include "pch.h"
#include "framework.h"
#include "Product.h"
#include <functional>

Ingredient::Ingredient() : name(""), volume(0.0) {} // Реализация Ingredient

Ingredient::Ingredient(const std::string& name_, double volume_)
    : name(name_), volume(volume_) {
    if (volume < 0) {
        throw std::invalid_argument("Объём ингредиента не может быть отрицательным!");
    }
}

Ingredient::Ingredient(const Ingredient& other) : name(other.name), volume(other.volume) {}

Ingredient::~Ingredient() {}

void Ingredient::Display() const {
    std::cout << name << " (" << volume << " ед.)";
}

Commission::Commission() : address(""), inspectionDate(0) {} // Реализация Commission

Commission::Commission(const std::string& address_, const std::vector<Ingredient>& forbiddenIngredients_, int inspectionDate_)
    : address(address_), forbiddenIngredients(forbiddenIngredients_), inspectionDate(inspectionDate_) {
}

Commission::Commission(const Commission& other) : address(other.address), forbiddenIngredients(other.forbiddenIngredients),
inspectionDate(other.inspectionDate) {
}

Commission::~Commission() {
    std::cout << "Деструктор класса Commission запущен" << std::endl;
}

Commission& Commission::operator=(const Commission& other) {
    if (this != &other) {
        address = other.address;
        forbiddenIngredients = other.forbiddenIngredients;
        inspectionDate = other.inspectionDate;
    }
    return *this;
}

void Commission::Display() const {
    std::cout << "=== Информация о комиссии ===" << std::endl;
    std::cout << "Адрес комиссии: " << address << std::endl;
    std::cout << "Срок проверки: " << inspectionDate << " дней" << std::endl;
    std::cout << "Список запрещённых ингредиентов: " << std::endl;
    if (forbiddenIngredients.empty()) {
        std::cout << " Нет запрещённых ингредиентов" << std::endl;
    }
    else {
        for (const auto& ing : forbiddenIngredients) {
            std::cout << "  - ";
            ing.Display();
            if (ing.volume == 0) {
                std::cout << " (полностью запрещён)";
            }
            else {
                std::cout << " (превышение лимита при количестве, большем " << ing.volume << " ед.)";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "== Конец списка ==" << std::endl;
}

void Commission::addForbiddenIngredient(const Ingredient& ingredient) { // Функция для добавления запрещённого ингредиента
    auto it = std::find(forbiddenIngredients.begin(), forbiddenIngredients.end(), ingredient);
    if (it == forbiddenIngredients.end()) {
        forbiddenIngredients.push_back(ingredient);
        std::cout << "Ингредиент ";
        ingredient.Display();
        std::cout << " добавлен в список запрещённых ингредиентов" << std::endl;
    }
    else {
        std::cout << "Ингредиент " << ingredient.name << " уже есть в списке запрещённых" << std::endl;
    }
}

bool Commission::check(const Product& product) const {
    std::cout << "Проверка товара " << product.getName() << "на легальность:" << std::endl;

    if (!product.checkExpiration(inspectionDate)) {
        std::cout << "Товар не прошёл проверку: срок годности истёк" << std::endl;
        return false;
    }

    auto composition = product.getComposition();

    for (const auto& forbidden : forbiddenIngredients) {
        for (const auto& ingredient : composition) {
            if (forbidden.volume == 0) {
                std::cout << "Товар не прошёл проверку: содержит полностью запрещённый ингредиент" << ingredient.name << std::endl;
                return false;
            }
            else if (ingredient.volume > forbidden.volume) {
                std::cout << "Товар не прошёл проверку: ингредиент" << ingredient.name << " превышает лимит (" << 
                    ingredient.volume << " > " << forbidden.volume << ")" << std::endl;
                return false;
            }
            else {
                std::cout << "Указанное количество ингредиента " << ingredient.name << " допустимо (" 
                    << ingredient.volume << " < " << forbidden.volume << ")" << std::endl;
            }
        }
    }
    std::cout << "Товар прошёл проверку!" << std::endl;
    return true;
}

Product::Product() : name(""), description(""), price(0.0), expirationDate(0), place(""), composition() {} // Конструктор по умолчанию

Product::Product(const std::string& name_, const std::string& description_, // Конструктор полного заполнения
    float price_, int expirationDate_, const std::string& place_, const std::vector<Ingredient>& composition_)
    : name(name_), description(description_), price(price_), expirationDate(expirationDate_), place(place_), composition(composition_) {
    setPrice(price_);
}

Product::Product(const Product& other) : name(other.name), description(other.description), price(other.price), // Конструктор копирования 
expirationDate(other.expirationDate), place(other.place), composition(other.composition) {
}

Product::~Product() { // Деструктор
    composition.clear(); // Очистка вектора
    composition.shrink_to_fit();
    std::cout << "Деструктор класса Product запущен" << std::endl;
}

Product& Product::operator=(const Product& other) { // Оператор присваивания
    if (this != &other) {
        name = other.name;
        description = other.description;
        price = other.price;
        expirationDate = other.expirationDate;
        place = other.place;
        composition = other.composition;
    }
    return *this;
}

Product Product::operator+(const Product& other) const { // Оператор +
    Product result;

    result.name = "Смесь " + this->name + " и " + other.name;
    result.description = "Комбинация" + this->description + " и " + other.description;
    result.price = (this->price + other.price) * 0.9;
    result.expirationDate = std::min(this->expirationDate, other.expirationDate);
    result.place = "Какое-то место";
    result.composition = commonComposition(this->composition, other.composition);
    return result;
}

Product Product::operator-(const Product& other) const { // Оператор -
    Product result;

    result.name = "Выбор " + this->name + " без " + other.name;
    result.description = this->description + " (после вычитания)";
    result.price = this->price * 0.9;
    result.expirationDate = std::max(0, this->expirationDate - 2);
    result.place = this->place;
    result.composition = removeCommon(this->composition, other.composition);
    Ingredient pr("консервант Т1000", 0.5);
    result.composition.push_back(pr);
    return result;
}

Product& Product::operator-=(const Product& other) { // Оператор -=
    this->name = "Выбор " + this->name + " без " + other.name;
    this->description = this->description + " (после вычитания с присваиванием)";
    this->price = this->price * 0.9;
    this->expirationDate = std::max(0, this->expirationDate - 2);
    this->place = this->place + " (после вычитания с присваиванием)";
    removeCommon_(this->composition, other.composition);
    Ingredient pr("консервант Т1000", 0.5);
    this->composition.push_back(pr);
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
    std::cout << "Описание товара: " << description << std::endl;
    std::cout << "Цена товара: " << price << " руб" << std::endl;
    std::cout << "Срок годности товара: " << expirationDate << " дней" << std::endl;
    std::cout << "Место хранения товара: " << place << std::endl;
    std::cout << "Состав товара: ";
    if (composition.empty()) {
        std::cout << "не был указан" << std::endl;
    }
    else {
        for (size_t i = 0; i < composition.size(); ++i) {
            composition[i].Display();
            if (i < composition.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

void Product::DisplayPlace() const {
    std::cout << "Место получения товара " << name << ": " << place << std::endl;
}

void Product::DecreaseExpirationDate(int days) { // Уменьшение срока хранения
    if (days < 0) {
        throw std::invalid_argument("Количество дней не может быть отрицателльным!");
    }
    std::cout << "Уменьшение срока хранения на " << days << " дней:" << std::endl;
    if (expirationDate > days) {
        expirationDate -= days;
        std::cout << "Новый срок годности: " << expirationDate << " дней" << std::endl;
    }
    else {
        expirationDate = 0;
        std::cout << "Срок годности товара уже истек" << std::endl;
    }
}

bool Product::checkExpiration(int checkDate) const {
    return expirationDate >= checkDate;
}

// Функция для написания общего состава без повторов
std::vector<Ingredient> Product::commonComposition(const std::vector<Ingredient>& v1, const std::vector<Ingredient>& v2) {
    std::vector<Ingredient> result;
    for (const auto& item : v1) {
        bool found = false;
        for (auto& existing : result) {
            if (existing.name == item.name) {
                existing.volume += item.volume;
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(item);
        }
    }
    for (const auto& item : v2) {
        bool found = false;
        for (auto& existing : result) {
            if (existing.name == item.name) {
                existing.volume += item.volume;
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(item);
        }
    }
    return result;
}

// Функция для написания состава1 без состава2
std::vector<Ingredient> Product::removeCommon(const std::vector<Ingredient>& v1, const std::vector<Ingredient>& v2) {
    std::vector<Ingredient> result;
    for (const auto& item : v1) {
        bool found = false;
        double removeVolume = 0;
        for (const auto& toRemove : v2) {
            if (item.name == toRemove.name) {
                removeVolume = toRemove.volume;
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(item);
        }
        else {
            if (item.volume > removeVolume) {
                Ingredient reduced = item;
                reduced.volume -= removeVolume;
                result.push_back(reduced);
            }
        }
    }
    return result;
}

// Отдельная функция для оператора -=
void Product::removeCommon_(std::vector<Ingredient>& target, const std::vector<Ingredient>& toRemove) {
    for (const auto& rem : toRemove) {
        for (auto it = target.begin(); it != target.end(); ) {
            if (it->name == rem.name) {
                if (it->volume > rem.volume) {
                    it->volume -= rem.volume;
                    ++it;
                }
                else {
                    it = target.erase(it);
                }
            }
            else {
                ++it;
            }
        }
    }
}
