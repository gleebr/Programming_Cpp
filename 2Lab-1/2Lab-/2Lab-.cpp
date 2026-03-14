#include <iostream>
#include <string>
#include <stdexcept>

class Product {

private:
    std::string name; // Поля
    std::string description;
    float price;
    int expirationDate;
    std::string location;

protected:
    std::string barCode;

public:
    Product() : name(""), description(""), price(0.0), expirationDate(0), location(""), barCode("") {} // Конструктор по умолчанию

    Product(const std::string& name, const std::string& description, // Конструктор полного заполнения
        float price, int expirationDate, const std::string& location, const std::string& barCode)
        : name(name), description(description), expirationDate(expirationDate), location(location), barCode(barCode) {
        setPrice(price);
    }

    Product(const Product& other) : name(other.name), description(other.description), price(other.price), // Конструктор копирования
        expirationDate(other.expirationDate), location(other.location), barCode(other.barCode) {}

    ~Product() { // Деструктор
        std::cout << "Деструктор класса Product запущен" << std::endl;
    }
    // Методы
    void setPrice(float price_) { // Сеттер для цены
        if (price_ >= 0) {
            price = price_;
        }
        else {
            throw std::invalid_argument("Цена не может быть отрицательной");
        }
    }

    void setBarCode(std::string& barCode_) { // Сеттер для штрихкода
        for (char c : barCode_) {
            if (!isdigit(c)) {
                throw std::invalid_argument("В штрихкоде должны быть только цифры");
            }
        }
        barCode = barCode_;
    }

    std::string getName() const { return name; } // Геттеры
    std::string getDescription() const { return description; }
    float getPrice() const { return price; }
    int getExpirationDate() const { return expirationDate; }
    std::string getLocation() const { return location; }
    std::string getBarCode() const { return barCode; }

    void Display() const { // Вывод всей информации
        std::cout << "Название товара: " << name << std::endl;
        std::cout << "Описание товара: " << description << std::endl;
        std::cout << "Цена товара: " << price << " руб" << std::endl;
        std::cout << "Срок годности товара: " << expirationDate << " дней" << std::endl;
        std::cout << "Место храниения товара: " << location << std::endl;
        std::cout << "Штрихкод товара: " << barCode << std::endl;
    }

    void DisplayLocation(const std::string& receiptInfo) const { // Вывод информации о месте
        std::cout << "Вывод информации о месте" << std::endl;
        std::cout << "Название товара: " << name << std::endl;
        std::cout << "Место храниения товара: " << location << std::endl;
        std::cout << "Информация о месте: " << receiptInfo << std::endl;
    }

    void DecreaseExpirationDate() { // Уменьшение срока хранения на 1 день
        std::cout << "Уменьшение срока хранения на 1 день:" << std::endl;
        if (expirationDate > 0) {
            expirationDate--;
        }
        else {
            std::cout << "Срок годности товара уже истёк" << std::endl;
        }
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");
    
    std::cout << "Вывод информации о продукте 1 через полное заполнение:" << std::endl;
    Product product1("Масло", "Масло сливочное", 229.99, 30, "Склад №2", "25689365984"); // Использование конструктора полного заполнения
    product1.Display();
    std::cout << std::endl;
    product1.DisplayLocation("Забрать в течение недели");
    std::cout << std::endl;
    product1.DecreaseExpirationDate();
    std::cout << "Новый срок годности: " << product1.getExpirationDate() << " дней" << std::endl;
    std::cout << std::endl;

    Product product2; // Использование конструктора по умолчанию
    std::cout << "Вывод информации о продукте 2 по умолчанию:" << std::endl;
    product2.Display();
    std::cout << std::endl;

    Product product3 = product1; // Использование конструктора копирования
    std::cout << "Вывод информации о продукте 3 путём копирования продукта 1:" << std::endl;
    product3.Display();
    std::cout << std::endl;

    try {
        product1.setPrice(259.99);
        std::cout << "Новая цена: " << product1.getPrice() << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }
    
    return 0;
}