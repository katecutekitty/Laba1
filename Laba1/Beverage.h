#pragma once

#include "utils.h"
#include "Menu.h"
#include <string>
#include <vector>
#include <iostream>


class Beverage : public Menu {
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

