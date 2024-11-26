#pragma once

#include "utils.h"
#include "Menu.h"
#include <vector>
#include <string>
#include <iostream>


class Dish : public Menu
{ 

    public:
        int weight;
        static shared_ptr<Menu> makeMenuFromString(string input, int weight);
        void showMenu();
        int getWeight();
};

