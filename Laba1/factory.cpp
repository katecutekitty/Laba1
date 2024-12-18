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
        if (std::count(input.begin(), input.end(), ';') != 4) throw InvalidStringFormatException("Некорректное число разделителей"); 
        else {
            string dishType = input.substr(0, input.find(';'));
            string baseDishArgs = input.substr(input.find(';') + 1, input.find_last_of(';') - input.find(';') - 1);
            string thisDishArgument = input.substr(input.find_last_of(';') + 1);

            return make_tuple(dishType, baseDishArgs, thisDishArgument);
        }
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
        tuple<string, string, string> args = parseInput(input);
        if (get<0>(args).empty() || get<1>(args).empty() || get<2>(args).empty() || std::count(input.begin(), input.end(), ';') != 4) throw InvalidStringFormatException("");
        else
            menuCollection.push_back(createMenuItem(get<0>(args), get<1>(args), get<2>(args)));
    }
    return menuCollection;
}

