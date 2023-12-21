#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Pizza {
protected:
    string name;
    string description;
    int size;
    double basePrice;
    int saltCount;
    int cheeseCount;

public:
    Pizza(const string& pizzaName, const string& pizzaDesc, int pizzaSize)
        : name(pizzaName), description(pizzaDesc), size(pizzaSize), saltCount(0), cheeseCount(0) {
        // Установка базовой цены в зависимости от размера
        switch (size) {
            case 25:
                basePrice = 10.0;
                break;
            case 30:
                basePrice = 15.0;
                break;
            case 35:
                basePrice = 20.0;
                break;
            case 40:
                basePrice = 25.0;
                break;
            default:
                basePrice = 0.0;
        }
    }

    // Функция для подсоления пиццы
    void addSalt(int times) {
        saltCount += times;
        basePrice += times * 0.5;
        cout << "Salt added to the pizza. New price: $" << basePrice << "\n";
    }

    // Функция для добавления сыра
    virtual void addCheese(int times) {
        cheeseCount += times;
        basePrice += times * 1.5;
        cout << "Cheese added to the pizza. New price: $" << basePrice << "\n";
    }

    // Функция для получения общей стоимости пиццы
    double getTotalPrice() const {
        return basePrice;
    }

    // Виртуальная функция для вывода информации о пицце
    virtual void displayInfo() const {
        cout << "Pizza: " << name << "\nDescription: " << description
                  << "\nSize: " << size << " cm\nBase Price: $" << basePrice
                  << "\nSalt Count: " << saltCount << "\nCheese Count: " << cheeseCount << "\n";
    }
};



class VegetarianPizza : public Pizza {
private:
    int vegetablesCount;

public:
    VegetarianPizza(const string& pizzaName, const string& pizzaDesc, int pizzaSize)
        : Pizza(pizzaName, pizzaDesc, pizzaSize), vegetablesCount(20) {}

    // Переопределение метода добавления сыра
    void addCheese(int times) override {
        cheeseCount += times;
        basePrice += times * 0.8; // У вегетарианской пиццы добавление сыра дешевле
        cout << "Cheese added to the vegetarian pizza. New price: $" << basePrice << "\n";
    }

    // Переопределение метода для вывода информации о вегетарианской пицце
    void displayInfo() const override {
        Pizza::displayInfo();
        cout << "Vegetables Count: " << vegetablesCount << "\n";
    }
};



class PepperoniPizza : public Pizza {
private:
    int pepperoniCount;

public:
    PepperoniPizza(const string& pizzaName, const string& pizzaDesc, int pizzaSize)
        : Pizza(pizzaName, pizzaDesc, pizzaSize), pepperoniCount(20) {}

    // Переопределение метода для вывода информации о пицце с пепперони
    void displayInfo() const override {
        Pizza::displayInfo();
        cout << "Pepperoni Count: " << pepperoniCount << "\n";
    }
};



class Order {
private:
    vector<Pizza*> pizzas;

public:
    // Функция для добавления пиццы в заказ
    void addPizza(Pizza* pizza) {
        pizzas.push_back(pizza);
    }

    // Функция для вывода информации о заказе
    void displayOrder() const {
        cout << endl;
        cout << "----------------------------------\n";
        cout << "Order Details:\n";

        for (const auto& pizza : pizzas) {
            pizza->displayInfo();
            cout << "----------------------------------\n";
        }

        double totalAmount = 0.0;
        for (const auto& pizza : pizzas) {
            totalAmount += pizza->getTotalPrice();
        }

        cout << "Total Amount: $" << totalAmount << "\n";
    }
};


// Функция для отображения меню и выбора пиццы
Pizza* selectPizzaFromMenu() {
    int choice;
    cout << "Menu:\n";
    cout << "1. Vegetarian Pizza\n";
    cout << "2. Pepperoni Pizza\n";
    cout << "Enter the number of the pizza you want to order: ";
    cin >> choice;

    int pizzaSize;

    cout << "Choose the size of the pizza (25, 30, 35, 40): ";
    cin >> pizzaSize;

    switch (choice) {
        case 1:
            return new VegetarianPizza("vegetarian", "polezno", pizzaSize);
        case 2:
            return new PepperoniPizza("pepperoni", "vkusno", pizzaSize);
        default:
            cout << "Invalid choice. Defaulting to a regular pizza.\n";
            return new Pizza("standart pizza", "norm pizza", pizzaSize);
    }
}


int main() {
    Order order;

    while (true) {
        cout << "1. Add Pizza to Order\n";
        cout << "2. Display Order\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                Pizza* pizza = selectPizzaFromMenu();

                int saltCount, cheeseCount;
                cout << "Enter the number of times to add salt to the pizza: ";
                cin >> saltCount;

                cout << "Enter the number of times to add cheese to the pizza: ";
                cin >> cheeseCount;

                pizza->addSalt(saltCount);
                pizza->addCheese(cheeseCount);

                order.addPizza(pizza);
                break;
            }
            case 2:
                order.displayOrder();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
