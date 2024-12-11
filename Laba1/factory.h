#ifndef UTILSH

#pragma once

#include <string> 
#include "Menu.h"
#include "utils.h"

using namespace std;

vector<shared_ptr<Menu>> makeMenuCollection(const vector<string>& inputStrings);

tuple<string, string, string> parseInput(const string& input);

shared_ptr<Menu> createMenuItem(const string& dishType, const string& baseDishArgs, const string& thisDishArgument);

#endif 

