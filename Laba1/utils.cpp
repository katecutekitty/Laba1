#include <string>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include "utils.h"
#include "InvalidStringFormatException.h"
#pragma once;

std::pair<chrono::hours, chrono::minutes> makeTimeFromString(std::string t) {
    std::string minStr, hrStr;
    std::pair<chrono::hours, chrono::minutes> time;
    hrStr = t.substr(0, t.find(':'));
    minStr = t.substr(t.find(':') + 1);
    time = make_pair(chrono::hours{ stoi(hrStr) }, chrono::minutes{ stoi(minStr) });
    return time;
}

std::vector<std::string> divideStringIntoParameters(std::string input) {
    vector<string> args(4);
    args[0] = input.substr(0, input.find(';'));
    input = input.substr(input.find(';') + 1);
    args[1] = input.substr(0, input.find(';'));
    args[2] = input.substr(input.find(';') + 1);

    

    return args;
}

std::vector<std::string> readFromFile(std::string filePath) {
    vector<string> inputStrings;
    string str;

    fstream in(filePath);

    if (in.is_open()) {
        while (getline(in, str)) {
            inputStrings.push_back(str);
        }
    }

    in.close();

    return inputStrings;
}

void validateArgs(const vector<string>& args, int lastParam) {
    if (args.size() < 3) {
        throw InvalidStringFormatException("Неверный формат строки: недостаточно параметров.");
    }
    if (stod(args[1]) <= 0 || lastParam <= 0) {
        throw InvalidStringFormatException("Цена и объём должны быть положительными числами.");
    }
}