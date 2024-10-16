#pragma once

#include <chrono>
#include <string>
#include <shared_mutex>

using namespace std;

class Menu
{
public:
    string title;
    double price;
    pair<chrono::hours, chrono::minutes> preparationTime;

    virtual ~Menu() = default;

    virtual shared_ptr<Menu> makeMenuFromString(string input) { }
    virtual void showMenu() {}
};

