#include "Menu.h"
#include "Dish.h"
#include "utils.h"

class Dish : public Menu {
	int weight;
public:
	static shared_ptr<Menu> makeMenuFromString(string input, int weight) {
		auto dish = make_shared<Dish>();
		vector<string> args = divideStringIntoParameters(input);

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