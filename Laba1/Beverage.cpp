#include "Beverage.h"
#include "Menu.h"
#include "utils.h"

class Beverage : public Menu {
	int volume;
public:
	static shared_ptr<Menu> makeMenuFromString(string input, int volume) {
		auto bev = make_shared<Beverage>();
		vector<string> args = divideStringIntoParameters(input);

		bev->title = args[0];
		bev->price = stod(args[1]);
		bev->preparationTime = makeTimeFromString(args[2]);
		bev->volume = volume;

		return bev;
	}

	void showMenu() {
		cout << "Напиток: " << title << ", Цена: " << price << " рублей, Вес: " << volume << " г\n";
	}
};