#include "factory.h"
#include "Menu.h"
#include "Dish.h"
#include "Beverage.h"
#include <string>
#include <vector>

#pragma once;

using namespace std;

vector<shared_ptr<Menu>> foo(vector<string> inputStrings) {
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
}
