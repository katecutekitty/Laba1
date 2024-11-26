#include "TestFramework.h"
#include "Dish.h"
#include "Beverage.h"
#include "utils.h"
#include "factory.h"

int main() {
    TestFramework::runTests();
    return 0;
}

TEST(MakeDish) {
    std::string input = "Dish;Salad;350;15:00";
    auto dish = Dish::makeMenuFromString(input.substr(input.find(';')), 150);

    ASSERT_EQ("Salad", dish->title);             // Проверка строки
    ASSERT_EQ(350.0, dish->price);                  // Проверка double
    ASSERT_EQ(150, dynamic_cast<Dish*>(dish.get())->getWeight()); // Проверка целого числа
}

TEST(MakeBeverage) {
    std::string input = "Beverage;Coffee;200,0;5:00";
    auto bev = Beverage::makeMenuFromString(input.substr(input.find(';')), 200);

    ASSERT_EQ("Coffee", bev->title);            // Проверка строки
    ASSERT_EQ(200.0, bev->price);                   // Проверка double
    ASSERT_EQ(200, dynamic_cast<Beverage*>(bev.get())->getVolume()); // Проверка целого числа
}

TEST(InvalidInput) {
    std::string invalidInput = "Dish;Salad;invalidPrice;15:00";
    try {
        auto dish = Dish::makeMenuFromString(invalidInput.substr(invalidInput.find(';')+1), 150);
        ASSERT_TRUE(false); // Эта строка не должна выполниться
    } catch (const std::exception& e) {
        ASSERT_EQ(std::string("Invalid input format"), e.what()); // Проверка ошибки
    }
}
