#include "factory.h"
#include "Menu.h"
#include "Dish.h"
#include "Beverage.h"
#include <string>
#include <vector>
#include "utils.h"
#include "InvalidStringFormatException.h"   

#pragma once;

using namespace std;

// разбор строки на аргументы
tuple<string, string, string> parseInput(const string& input) {
    string dishType = input.substr(0, input.find(';'));
    string baseDishArgs = input.substr(input.find(';') + 1, input.find_last_of(';') - input.find(';'));
    string thisDishArgument = input.substr(input.find_last_of(';') + 1);
    return make_tuple(dishType, baseDishArgs, thisDishArgument);
}

// создание объекта меню
shared_ptr<Menu> createMenuItem(const string& dishType, const string& baseDishArgs, const string& thisDishArgument) {
    if (dishType == "Напиток" || dishType == "Beverage") {
        return Beverage::makeMenuFromString(baseDishArgs, stoi(thisDishArgument));
    }
    else if (dishType == "Блюдо" || dishType == "Dish") {
        return Dish::makeMenuFromString(baseDishArgs, stoi(thisDishArgument));
    }
    else {
        throw InvalidStringFormatException("Неизвестный тип блюда: " + dishType);
    }
}

vector<shared_ptr<Menu>> makeMenuCollection(const vector<string>& inputStrings) {
    vector<shared_ptr<Menu>> menuCollection;

    for (const auto& input : inputStrings) {
        try {
            tuple<string,string,string> args = parseInput(input);
            menuCollection.push_back(createMenuItem(get<0>(args), get<1>(args), get<2>(args)));
        }
        catch (const InvalidStringFormatException& e) {
            cerr << "Ошибка обработки строки: " << e.what() << endl;
        }
        catch (const exception& e) {
            cerr << "Общая ошибка: " << e.what() << endl;
        }
    }

    return menuCollection;
}


/*vector<shared_ptr<Menu>> foo(vector<string> inputStrings) {
    vector<shared_ptr<Menu>> menuCollection;
    for (int i = 0; i < inputStrings.size(); ++i) {

        string input = inputStrings[i], dishType, baseDishArgs, thisDishArgument;

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
    return menuCollection;
}*/
