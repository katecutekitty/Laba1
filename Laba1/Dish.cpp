#include "Menu.h"
#include "Dish.h"

class Dish : public Menu {
	int weight;
public:
	static shared_ptr<Menu> makeMenuFromString(string input, int weight) {
		auto dish = make_shared<Dish>();
		vector<string> args(4);

		args[0] = input.substr(1, input.find(';') - 2);
		input = input.substr(input.find(';') + 1);
		args[1] = input.substr(0, input.find(';'));
		args[2] = input.substr(input.find(';') + 1);

		dish->title = args[0];
		dish->price = stod(args[1]);
		dish->preparationTime = makeTimeFromString(args[2]);
		dish->weight = weight;

		return dish;
	}

	void showMenu() {
		cout << "Блюдо: " << title << ", Цена: " << price << " рублей, Вес: " << weight << " г\n";
	}
};