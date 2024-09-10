#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Menu {
    string title;
    double price;
    tm preparationTime;
};

bool stringValidation(string str) {
    int divisorCount = 0, bracketsCount = 0, colonCount = 0, commaCount = 0;
    for (auto i : str) {
        if (i == ';') ++divisorCount;
        if (i == '"') ++bracketsCount;
        if (i == ':' && divisorCount == 2) ++colonCount;
        if (i == ',' && divisorCount == 1) ++commaCount;
    }
    if (divisorCount == 2 && bracketsCount == 2 && colonCount == 1 && commaCount == 1)
        return 1;
    else
        return 0;
}

tm makeTimeFromString(string t) {
    string minStr, hrStr;
    tm time;
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] == ':') {
            hrStr = t.substr(0, i);
            minStr = t.substr(i + 1, t.size() - i - 1);
            break;
        }
    }
    time.tm_hour = stoi(hrStr);
    time.tm_min = stoi(minStr);
    return time;
}

Menu makeMenuFromString(string input) {
    vector<string> args;
    int prevDivisorPosition = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == ';' && prevDivisorPosition == 0) {
            args.push_back(input.substr(1, i - 2));
            prevDivisorPosition = i;
        }
        else if (input[i] == ';' && args.size() == 1) {
            args.push_back(input.substr(prevDivisorPosition + 1, i - prevDivisorPosition - 1));
            prevDivisorPosition = i;
        }
        else if (args.size() == 2 && i == input.size() - 1) {
            args.push_back(input.substr(prevDivisorPosition + 1, i));
        }
    }
    return Menu{args[0], stod(args[1]), makeTimeFromString(args[2])};
}

int main()
{
    setlocale(0, "rus");
    cout << "Введите строку в формате: ''Название блюда из меню'';цена(разделитель - запятая);время приготовления(разделитель - двоеточие)\n";
    string input;
    getline(cin, input);
    while (stringValidation(input) == 0) {
        cout << "Ой! Формат строки не подходит. Попробуйте ещё раз\n";
        getline(cin, input);
    }
    Menu menu = makeMenuFromString(input);
    cout << menu.title << ' ' << menu.price << ' ' << menu.preparationTime.tm_hour << ':' << menu.preparationTime.tm_min;
}