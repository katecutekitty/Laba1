#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <format>
#include "utils.h"

using namespace std;

struct Menu {
    string title;
    double price;
    pair<chrono::hours, chrono::minutes> preparationTime;

    virtual ~Menu() = default;

    virtual shared_ptr<Menu> makeMenuFromString(string input) { return nullptr; }
    virtual void showMenu() {}
};

//использовать dynamic_cast<Dish*>(m)

struct Dish : public Menu {
    int weight;

    public :
    static shared_ptr<Menu> makeMenuFromString(string input, int weight) {

        auto dish = make_shared<Dish>();
        vector<string> args(4);

        args[0] = input.substr(1, input.find(';') - 2);
        input = input.substr(input.find(';') + 1);
        args[1] = input.substr(0, input.find(';'));
        args[2] = input.substr(input.find(';') + 1);

        dish->title = args[0];
        dish->price = stod(args[1]);
        dish->preparationTime = makeTimeFromString(args[2]);
        dish->weight = weight;

        return dish;
    }

    void showMenu() {
        cout << "Блюдо: " << title << ", Цена: " << price << " рублей, Вес: " << weight << " г\n";
    }
};

struct Beverage : public Menu {
    int volume;

    public:
    static shared_ptr<Menu> makeMenuFromString(string input, int volume) {

        auto bev = make_shared<Beverage>();
        vector<string> args(4);

        args[0] = input.substr(1, input.find(';') - 2);
        input = input.substr(input.find(';') + 1);
        args[1] = input.substr(0, input.find(';'));
        args[2] = input.substr(input.find(';') + 1);

        bev->title = args[0];
        bev->price = stod(args[1]);
        bev->preparationTime = makeTimeFromString(args[2]);
        bev->volume = volume;

        return bev;
    }
    void showMenu() {
        cout << "Напиток: " << title << ", Цена: " << price << " рублей, Объём: " << volume << " мл\n";
    }
};

//string filePath = "C:\\Users\\User\\Desktop\\fileSource.txt";

vector<string> readFromFile(string filePath) {
    vector<string> inputStrings;
    string str;

    fstream in(filePath);

    if (in.is_open()) {
        while (getline(in, str)) {
            inputStrings.push_back(str);
        }
    }

    in.close();

    return inputStrings;
}

int main()
{
    setlocale(0, "rus");
    string input, dishType, baseDishArgs, thisDishArgument;

    int inputType;

    vector<string> inputStrings;

    cout << "Выберите, откуда считать данные:\n1 - Текстовый файл\n2 - Консоль\n";

    cin >> inputType;

    if (inputType == 1) {
        string filePath;
        cout << "Введите путь к файлу\n";

        cin >> filePath;

        inputStrings = readFromFile(filePath);
    }

    else {
        int objectsCount;

        cout << "Введите количество объектов, которые Вы хотите внести\n";
        cin >> objectsCount;

        inputStrings.resize(objectsCount);

        cout << "Введите строку в формате : \nТип блюда с заглавной буквы; ''Название блюда из меню''; цена(разделитель - запятая); время приготовления(разделитель - двоеточие); масса / объём(в зависимости от типа блюда)\nРазделитель - клавиша Enter";
        
        for (int i = 0; i < objectsCount; ++i) {
            cin >> inputStrings[i];
        }
    }

    vector<shared_ptr<Menu>> menuCollection;

    for (int i = 0; i < inputStrings.size(); ++i) {

        input = inputStrings[i];

        //тип блюда - первое свойство во входных данных
        dishType = input.substr(0, input.find(';'));

        //основные свойства, относящиеся ко всем объектам из меню (Меню, Блюдо, Напиток)
        baseDishArgs = input.substr(input.find(';') + 1, input.find_last_of(';') - input.find(';'));

        //последнее свойство во входных данных обозначает либо вес, либо объем,
        //в зависимости от указанного типа объекта
        thisDishArgument = input.substr(input.find_last_of(';') + 1);

        if (dishType == "Напиток" || dishType == "Beverage") {
            auto bev = Beverage::makeMenuFromString(baseDishArgs, stoi(thisDishArgument));
            menuCollection.push_back(bev);
        }
        else if (dishType == "Dish" || dishType == "Блюдо") {
            auto dish = Dish::makeMenuFromString(baseDishArgs, stoi(thisDishArgument));
            menuCollection.push_back(dish);
        }
    }

    if (menuCollection.size() > 0) {
        cout << "\n                        МЕНЮ\n";
        for (auto& item : menuCollection) {
            item->showMenu();
        }
    }

    return 0;
}