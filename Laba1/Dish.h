#pragma once

#include "utils.h"
#include "Menu.h"
#include <vector>
#include <string>
#include <iostream>


class Dish : public Menu
{ int weight;

    public:

        static shared_ptr<Menu> makeMenuFromString(string input, int weight);
        void showMenu();
};

