#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

struct Person { // Структура для представления каждого человека
    std::string FullName;
    int age;
    bool isIntrovert;
    std::vector <Person*> friends;
    Person(std::string name, int personAge, bool introvert = false) : FullName(name), age(personAge), isIntrovert(introvert) {}
};

std::vector <Person*> list;

void DisplayPerson() { // Функция для вывода одного конкретного человека
    std::cout << "Просмотр одного человека по номеру" << std::endl;

    if (list.empty()) {
        std::cout << "Пусто" << std::endl;
        return;
    }

    for (size_t i = 0; i < list.size(); i++) {
        std::cout << i + 1 << ". " << list[i]->FullName << std::endl;
    }

    std::cout << "Выберите номер человека: ";
    int ind;
    std::cin >> ind;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (ind < 1 || ind > static_cast<int>(list.size())) {
        std::cout << "Такого номера нет!" << std::endl;
        return;
    }

    Person* x = list[ind - 1];

    std::cout << "Имя: " << x->FullName << std::endl;
    std::cout << "Возраст: " << x->age << std::endl;
    std::cout << "Интроверт: " << (x->isIntrovert ? "Да" : "Нет") << std::endl;
    std::cout << "Друзья (" << x->friends.size() << "): ";

    if (x->friends.empty()) {
        std::cout << "Нет друзей";
    }
    else {
        for (size_t i = 0; i < x->friends.size(); i++) {
            std::cout << x->friends[i]->FullName;
            if (i != x->friends.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

void Create() { // Функция для создания нового человека
    std::cout << "Создание нового человека" << std::endl;
    std::string name;
    char choice;
    int age;
    bool isIntrovert;

    std::cout << "Введите имя (без повторений): ";
    std::cin >> name;

    for (const auto& person : list) {
        if (person->FullName == name) {
            std::cout << "Человек с таким именем уже есть!" << std::endl;
            return;
        }
    }

    std::cout << "Введите возраст: ";
    std::cin >> age;

    std::cout << "Интроверт? (да/нет) ";
    std::cin >> choice;
    isIntrovert = (choice == 'да');

    Person* newPerson = new Person(name, age, isIntrovert);
    list.push_back(newPerson);
    std::cout << "Создано!" << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Friendship() { // Функция для установки дружеских отношений
    if (list.size() <= 2) {
        std::cout << "Недостаточно людей" << std::endl;
        return;
    }

    std::cout << "Установление дружеских связей..." << std::endl;
    std::cout << "Список людей: " << std::endl;
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << i + 1 << ". " << list[i]->FullName;
        if (list[i]->isIntrovert) {
            std::cout << " (интроверт)";
        }
        std::cout << std::endl;
    }

    int index1, index2;
    std::cout << "Выберите номер первого человека: ";
    std::cin >> index1;
    std::cout << "Выберите номер второго человека: ";
    std::cin >> index2;

    if (index1 < 1 || index1 > static_cast<int>(list.size()) || index2 < 1 || index2 > static_cast<int>(list.size())) {
        std::cout << "Такого номера нет!" << std::endl;
        return;
    }

    index1 -= 1;
    index2 -= 1;

    if (index1 == index2) {
        std::cout << "Человеку нельзя дружить самому с собой!" << std::endl;
        return;
    }

    Person* person1 = list[index1];
    Person* person2 = list[index2];

    if (person1->isIntrovert || person2->isIntrovert) {
        std::cout << "Ошибка! Интроверту нельзя образовать дружественную связь!" << std::endl;
        return;
    }

    for (const auto& friendPtr : person1->friends) {
        if (friendPtr == person2) {
            std::cout << "Эти люди уже дружат!" << std::endl;
            return;
        }
    }

    person1->friends.push_back(person2);
    person2->friends.push_back(person1);

    std::cout << "Дружеские связи установлены!" << std::endl;
}

void ViewAllPeople() { // Функция для просмотра всех людей и их характеристик
    std::cout << "Просмотр всех людей..." << std::endl;
    
    if (list.empty()) {
        std::cout << "Пусто" << std::endl;
        return;
    }

    for (const auto& person : list) {
        std::cout << "Имя: " << person->FullName << std::endl;
        std::cout << "Возраст: " << person->age << std::endl;
        std::cout << "Интроверт: " << (person->isIntrovert ? "Да" : "Нет") << std::endl;
        std::cout << "Друзья (" << person->friends.size() << "): ";

        if (person->friends.empty()) {
            std::cout << "Нет друзей";
        }
        else {
            for (size_t i = 0; i < person->friends.size(); i++) {
                std::cout << person->friends[i]->FullName;
                if (i != person->friends.size() - 1) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << std::endl;
    }
}

void SecretChain() { // Функция 1 варианта 5 (цепочка людей, узнающих секрет)
    if (list.empty()) {
        std::cout << "Журнал пуст" << std::endl;
        return;
    }

    std::cout << "Цепочка людей, узнающих секрет" << std::endl;
    std::cout << "Выберите человека, которому доверите секрет: " << std::endl;
    
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << i + 1 << ". " << list[i]->FullName << std::endl;
    }

    int choice2;
    std::cin >> choice2;
    if (choice2 < 1 || choice2 > static_cast<int>(list.size())) {
        std::cout << "Такого номера нет!" << std::endl;
        return;
    }

    Person* startP = list[choice2 - 1];

    std::vector <Person*> last;
    std::vector <Person*> queue;

    last.push_back(startP);
    queue.push_back(startP);

    std::cout << "Цепоска распространения секрета от " << startP->FullName << ": " << std::endl;
    std::cout << startP->FullName;

    size_t i = 0;
    while (i < queue.size()) {
        Person* curent = queue[i];

        for (Person* friendPtr : curent->friends) {
            if (std::find(last.begin(), last.end(), friendPtr) == last.end()) {
                last.push_back(friendPtr);
                queue.push_back(friendPtr);
                std::cout << " -> " << friendPtr->FullName;
            }
        }
        i++;
    }
    std::cout << std::endl;
}

void ShowIntroverts() { // Функция 2 варианта 5 (показ всех интровертов)
    std::cout << "Список всех интровертов (друзей нет)" << std::endl;

    bool found = false;
    for (const auto& person : list) {
        if (person->isIntrovert && person->friends.empty()) {
            std::cout << person->FullName << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Интровертов не найдено" << std::endl;
    }
}

void BestFriends() { // Функция 3 варианта 5 (вери бест френдс)
    std::cout << "Пары 'вери бест френдс'" << std::endl;

    std::vector <std::pair<Person*, Person*>> pairs;

    for (size_t i = 0; i < list.size(); i++) {
        for (size_t j = i + 1; j < list.size(); j++) {
            Person* first = list[i];
            Person* second = list[j];

            bool fFriendsWithSecond = false;
            bool sFriendsWithFirst = false;

            for (const auto& friendPtr : first->friends) {
                if (friendPtr == second) {
                    fFriendsWithSecond = true;
                    break;
                }
            }

            for (const auto& friendPtr : second->friends) {
                if (friendPtr == first) {
                    sFriendsWithFirst = true;
                    break;
                }
            }

            if (fFriendsWithSecond && sFriendsWithFirst) {
                pairs.push_back(std::make_pair(first, second));
            }
        }
    }

    if (pairs.empty()) {
        std::cout << "Пар 'вери бест френдс' нет" << std::endl;
    }
    else {
        for (const auto& p : pairs) {
            std::cout << p.first->FullName << " <-> " << p.second->FullName << std::endl;
        }
    }
}

void StartList() { // Функция для создания начальных 10-ти человек
    for (auto& person : list) {
        delete person;
    }
    list.clear();

    Person* people[10] = {
        new Person("Иван", 25, false),
        new Person("Андрей", 30, false),
        new Person("Илья", 20, false),
        new Person("Никита", 26, true),
        new Person("Владимир", 22, false),
        new Person("Алексей", 19, false),
        new Person("Дмитрий", 27, true),
        new Person("Георгий", 31, false),
        new Person("Екатерина", 35, false),
        new Person("Елизавета", 22, true),
    };

    for (int i = 0; i < 10; i++) {
        list.push_back(people[i]);
    }

    people[0]->friends.push_back(people[1]);
    people[0]->friends.push_back(people[2]);
    people[0]->friends.push_back(people[7]);

    people[1]->friends.push_back(people[0]);
    people[2]->friends.push_back(people[4]);
    people[5]->friends.push_back(people[7]);
    people[8]->friends.push_back(people[5]);

    std::cout << "Создано 10 человек с дружескими связями" << std::endl;
}

void clean() { //Функция для очистки памяти
    for (auto& person : list) {
        delete person;
    }
    list.clear();
}

void Menu() { // Консольное меню
    int c;
    do {
        std::cout << "Меню команд:" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "1. Просмотр всех людей" << std::endl;
        std::cout << "2. Просмотр конкретного человека" << std::endl;
        std::cout << "3. Создание нового человека" << std::endl;
        std::cout << "4. Установить дружеские связи" << std::endl;
        std::cout << "5. Цепочка распространения секрета" << std::endl;
        std::cout << "6. Интроверты" << std::endl;
        std::cout << "7. Вери бест френдс" << std::endl;
        std::cout << "Выберите пункт: " << std::endl;

        std::cin >> c;

        switch (c) {
        case 0:
            std::cout << "Выход..." << std::endl;
            break;
        case 1:
            ViewAllPeople();
            break;
        case 2:
            DisplayPerson();
            break;
        case 3:
            Create();
            break;
        case 4:
            Friendship();
            break;
        case 5:
            SecretChain();
            break;
        case 6:
            ShowIntroverts();
            break;
        case 7:
            BestFriends();
            break;
        default:
            std::cout << "Такого пункта нет!" << std::endl;
            break;
        }
    } while (c != 0);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Программа 'Друзья'" << std::endl;

    StartList();
    Menu();

    clean();

    return 0;
}