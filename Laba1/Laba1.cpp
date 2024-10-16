#include <iostream>
#include <vector>
#include "utils.h"
#include "factory.h"

using namespace std;

//string filePath = "C:\\Users\\User\\Desktop\\fileSource.txt";

int main()
{
    setlocale(0, "rus");
    string input;

    int inputType;

    vector<string> inputStrings;

    cout << "Выберите, откуда считать данные:\n1 - Текстовый файл\n2 - Консоль\n";

    cin >> inputType;

    if (inputType == 1) {
        string filePath;
        cout << "Введите путь к файлу\n";

        cin >> filePath;

        inputStrings = readFromFile(filePath);
    }

    else {
        int objectsCount;

        cout << "Введите количество объектов, которые Вы хотите внести\n";
        cin >> objectsCount;

        inputStrings.resize(objectsCount);

        cout << "Введите строку в формате : \nТип блюда с заглавной буквы; ''Название блюда из меню''; цена(разделитель - запятая); время приготовления(разделитель - двоеточие); масса / объём(в зависимости от типа блюда)\nРазделитель - клавиша Enter";
        
        for (int i = 0; i < objectsCount; ++i) {
            cin >> inputStrings[i];
        }
    }

    vector<shared_ptr<Menu>> menuCollection = foo(inputStrings);

    if (menuCollection.size() > 0) {
        cout << "\n                        МЕНЮ\n";
        for (auto& item : menuCollection) {
            item->showMenu();
        }
    }

    return 0;
}