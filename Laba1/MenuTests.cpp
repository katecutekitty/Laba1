#include "MyTest.h"
#include "Dish.h"
#include "Beverage.h"
#include "utils.h"
#include "factory.h"
#include <iostream>
#include "InvalidStringFormatException.h"

int main() {
    setlocale(0, "rus");
    MyTest::runTests();
    return 0;
}

TEST(MakeDish) {
    std::string input = "Dish;Salad;350;15:00";
    auto dish = Dish::makeMenuFromString(input.substr(input.find(';')+1), 150);

    ASSERT_EQ("Salad", dish->title);             
    ASSERT_EQ(350.0, dish->price);                 
    ASSERT_EQ(150, dynamic_cast<Dish*>(dish.get())->getWeight()); 
}

TEST(MakeBeverage) {
    std::string input = "Beverage;Coffee;200,0;5:00";
    auto bev = Beverage::makeMenuFromString(input.substr(input.find(';')+1), 200);

    ASSERT_EQ("Coffee", bev->title);            
    ASSERT_EQ(200.0, bev->price);                   
    ASSERT_EQ(200, dynamic_cast<Beverage*>(bev.get())->getVolume()); 
}

TEST(InvalidInput_MissingSemicolon) {
    std::string input = "DishSalad35015:00";
    ASSERT_EXCEPTION(parseInput(input), InvalidStringFormatException);
}

TEST(InvalidInput_MissingLastArgument) {
    std::string input = "Salad;350;";
    ASSERT_EXCEPTION(divideStringIntoParameters(input), InvalidStringFormatException);
}

TEST(InvalidInput_ExtraSemicolon) {
    std::string input = ";;;Salad;350";  
    ASSERT_EXCEPTION(divideStringIntoParameters(input), InvalidStringFormatException);
}

TEST(InvalidInput_InvalidTimeFormat) {
    std::string input = "Dish;Salad;350,0;1500";  
    ASSERT_EXCEPTION(divideStringIntoParameters(input), InvalidStringFormatException);
}
