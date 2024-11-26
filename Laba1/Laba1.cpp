#include <iostream>
#include <vector>
#include "utils.h"
#include "factory.h"
#include "Menu.h"
#include "Beverage.h"
#include "Dish.h"

using namespace std;

//string filePath = "C:\\Users\\User\\Desktop\\fileSource.txt";

vector<string> getInputFromFile() {
    string filePath;
    cout << "Введите путь к файлу: ";
    cin >> filePath;
    return readFromFile(filePath);
}

vector<string> getInputFromConsole() {
    int objectsCount;
    cout << "Введите количество объектов, которые Вы хотите внести: ";
    cin >> objectsCount;

    vector<string> inputStrings(objectsCount);
    cout << "Введите строку в формате: Тип;Название;Цена;Время;Масса/Объём\n";

    cin.ignore();
    for (int i = 0; i < objectsCount; ++i) {
        getline(cin, inputStrings[i]);
    }

    return inputStrings;
}

int main()
{
    setlocale(0, "rus");
    string input;

    int inputType;

    vector<string> inputStrings;

    cout << "Выберите, откуда считать данные:\n1 - Текстовый файл\n2 - Консоль\n";

    cin >> inputType;

    if (inputType == 1) {
        inputStrings = getInputFromFile();
    }
    else {
        inputStrings = getInputFromConsole();
    }

    vector<shared_ptr<Menu>> menuCollection = makeMenuCollection(inputStrings);

    if (menuCollection.size() > 0) {
        cout << "\n                        МЕНЮ\n";
        for (auto& item : menuCollection) {
            item->showMenu();
        }
    }

    return 0;
}