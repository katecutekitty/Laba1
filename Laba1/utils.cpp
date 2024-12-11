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
        if (t.find(':') == std::string::npos) throw InvalidStringFormatException("Некорректное время");
        hrStr = t.substr(0, t.find(':'));
        minStr = t.substr(t.find(':') + 1);
        if (isalpha(hrStr[0]) || isalpha(hrStr[1]) || isalpha(minStr[0]) || isalpha(minStr[1])) throw InvalidStringFormatException("Некорректное время");
        time = make_pair(chrono::hours{ stoi(hrStr) }, chrono::minutes{ stoi(minStr) });
        return time;
}

std::vector<std::string> divideStringIntoParameters(std::string input) {
        vector<string> args;
        if (std::count(input.begin(), input.end(), ';') != 2) {
            throw InvalidStringFormatException("Некорректный формат строки: неверное число разделителей");
        }
        else {
            args.push_back(input.substr(0, input.find(';')));
            input = input.substr(input.find(';') + 1);
            args.push_back(input.substr(0, input.find(';')));
            args.push_back(input.substr(input.find(';') + 1));
            if (args.size() != 3 || args[0].size() == 0 || args[1].size() == 0 || args[2].size() == 0) {
                throw InvalidStringFormatException("Некорректный ввод");
            }
            else return args;
        }
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
        cout << "validateArgs";
        throw InvalidStringFormatException("Цена и объём должны быть положительными числами.");
    }
}