#include "Menu.h"
#include "Dish.h"
#include "utils.h"

shared_ptr<Menu> Dish::makeMenuFromString(string input, int weight) {
		auto dish = make_shared<Dish>();
		vector<string> args = divideStringIntoParameters(input.substr(input.find(';')+1));
		validateArgs(args, weight);

		dish->title = args[0];
		dish->price = stod(args[1]);
		dish->preparationTime = makeTimeFromString(args[2]);
		dish->weight = weight;

		return dish;
	}

	void Dish::showMenu() {
		cout << "Блюдо: " << title << ", Цена: " << price << " рублей, Вес: " << weight << " г\n";
	}
	int Dish::getWeight() {
		return weight;
	}
