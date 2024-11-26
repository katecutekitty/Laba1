#pragma once

#include "utils.h"
#include "Menu.h"
#include <string>
#include <vector>
#include <iostream>


class Beverage : public Menu 
{
    

public: 
    int volume;
    static shared_ptr<Menu> makeMenuFromString(string input, int volume);
    void showMenu();
    int getVolume();
};

