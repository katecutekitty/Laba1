#include "gtest/gtest.h"
#include "pch.h"
#include "../Laba1/utils.cpp"
#include "../Laba1/Dish.cpp"
#include "../Laba1/Beverage.cpp"
#include "../Laba1/factory.cpp"
#include "../Laba1/Menu.cpp"
#include "../Laba1/InvalidStringFormatException.h"

TEST(DishTest, MakeDish_ValidInput) {
    std::string input = "Salad;350,0;15:00";
    auto dish = Dish::makeMenuFromString(input, 150);

    EXPECT_EQ("Salad", dish->title);
    EXPECT_DOUBLE_EQ(350.0, dish->price);
    EXPECT_EQ(150, dynamic_cast<Dish*>(dish.get())->getWeight());
}

TEST(DishTest, MakeDish_InvalidInput) {
    std::string input = "InvalidData";
    EXPECT_THROW(Dish::makeMenuFromString(input, 150), InvalidStringFormatException);
}

TEST(BeverageTest, MakeBeverage_ValidInput) {
    std::string input = "Coffee;200,0;5:00";
    auto beverage = Beverage::makeMenuFromString(input, 200);

    EXPECT_EQ("Coffee", beverage->title);
    EXPECT_DOUBLE_EQ(200.0, beverage->price);
    EXPECT_EQ(200, dynamic_cast<Beverage*>(beverage.get())->getVolume());
}

TEST(BeverageTest, MakeBeverage_InvalidInput) {
    std::string input = "Beverage;Coffee;;5:00";
    EXPECT_THROW(Beverage::makeMenuFromString(input, 200), InvalidStringFormatException);
}

TEST(UtilsTest, DivideString_ValidInput) {
    std::string input = "Salad;350,0;15:00";
    std::vector<std::string> params = divideStringIntoParameters(input);

    ASSERT_EQ(params.size(), 3);
    EXPECT_EQ(params[0], "Salad");
    EXPECT_EQ(params[1], "350,0");
    EXPECT_EQ(params[2], "15:00");
}

TEST(UtilsTest, DivideString_InvalidInput) {
    std::string input = "Salad350:00";
    EXPECT_THROW(divideStringIntoParameters(input), InvalidStringFormatException);
}

TEST(FactoryTest, CreateMenuCollection_ValidInput) {
    std::vector<std::string> inputs = {
        "Dish;Salad;350,0;15:00;150",
        "Beverage;Coffee;200,0;5:00;200"
    };
    auto menu = makeMenuCollection(inputs);

    ASSERT_EQ(menu.size(), 2);
    EXPECT_EQ(menu[0]->title, "Salad");
    EXPECT_DOUBLE_EQ(menu[0]->price, 350.0);
    EXPECT_EQ(dynamic_cast<Dish*>(menu[0].get())->getWeight(), 150);

    EXPECT_EQ(menu[1]->title, "Coffee");
    EXPECT_DOUBLE_EQ(menu[1]->price, 200.0);
    EXPECT_EQ(dynamic_cast<Beverage*>(menu[1].get())->getVolume(), 200);
}

TEST(FactoryTest, CreateMenuCollection_InvalidInput) {
    std::vector<std::string> inputs = { "InvalidInput" };
    EXPECT_THROW(makeMenuCollection(inputs), InvalidStringFormatException);
}