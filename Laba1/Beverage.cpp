#include "Beverage.h"
#include "Menu.h"
#include "utils.h"

	shared_ptr<Menu> Beverage::makeMenuFromString(string input, int volume) {
		auto bev = make_shared<Beverage>();
		vector<string> args = divideStringIntoParameters(input.substr(input.find(';') + 1));
		validateArgs(args, volume);

		bev->title = args[0];
		bev->price = stod(args[1]);
		bev->preparationTime = makeTimeFromString(args[2]);
		bev->volume = volume;

		return bev;
	}

	void Beverage::showMenu() {
		cout << "Напиток: " << title << ", Цена: " << price << " рублей, Объём: " << volume << " мл\n";
	}

	int Beverage::getVolume() {
		return volume;
	}