#pragma once

#include <chrono>
#include <string>
#include <shared_mutex>
#include "utils.h"

using namespace std;

class Menu
{
public:
    string title;
    double price;
    pair<chrono::hours, chrono::minutes> preparationTime;

    virtual ~Menu() = default;
    virtual void showMenu();
};

