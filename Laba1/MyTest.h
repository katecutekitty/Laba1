#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>
#include "InvalidStringFormatException.h"

class MyTest {
public:
    static void registerTest(const std::string& name, const std::function<void()>& test) {
        getTests().push_back({ name, test });
    }

    static void runTests() {
        int passed = 0, failed = 0;
        for (const auto& p: getTests()) {
            std::cout << "Running test: " << p.first << std::endl;
            try {
                p.second();
                std::cout << "[PASSED] " << p.first << "\n";
                ++passed;
            }
            catch (const std::exception& e) {
                std::cerr << "[FAILED] " << p.first << ": " << e.what() << "\n";
                ++failed;
            }
        }
        std::cout << "\nTests passed: " << passed << "\n";
        std::cout << "Tests failed: " << failed << "\n";
    }

    template <typename T>
    static void assertEqual(const T& expected, const T& actual, const std::string& message = "") {
        if (expected != actual) {
            std::ostringstream oss;
            oss << (message.empty() ? "Values are not equal" : message)
                << "\nExpected: " << expected
                << ", Got: " << actual;
            throw std::runtime_error(oss.str());
        }
    }

    static void assertEqual(const std::string& expected, const std::string& actual, const std::string& message = "") {
        if (expected != actual) {
            std::ostringstream oss;
            oss << (message.empty() ? "Strings are not equal" : message)
                << "\nExpected: \"" << expected
                << "\", Got: \"" << actual << "\"";
            throw std::runtime_error(oss.str());
        }
    }

    static void assertTrue(bool condition, const std::string& message = "") {
        if (!condition) {
            throw std::runtime_error(message.empty() ? "Condition is false" : message);
        }
    }

    /*static void assertException(const std::function<void()>& func, const std::type_info& expectedExceptionType) {
        try {
            func();  // Выполняем функцию
            throw std::runtime_error("Expected exception of type " + std::string(expectedExceptionType.name()) + " but got none");
        }
        catch (const std::exception& e) {
            // Сравниваем тип выброшенного исключения с ожидаемым
            if (typeid(e) != expectedExceptionType) {
                throw std::runtime_error("Expected exception of type " + std::string(expectedExceptionType.name()) +
                    " but got exception of type " + typeid(e).name());
            }
        }
    }*/

private:
    static std::vector<std::pair<std::string, std::function<void()>>>& getTests() {
        static std::vector<std::pair<std::string, std::function<void()>>> tests;
        return tests;
    }
};

#define TEST(name) void name(); \
    static const bool name##_registered = \
        (MyTest::registerTest(#name, name), true); \
    void name()

#define ASSERT_TRUE(condition) MyTest::assertTrue(condition, #condition " failed")
#define ASSERT_EQ(expected, actual) MyTest::assertEqual((expected), (actual), "Assertion failed")
#define ASSERT_EXCEPTION(expr, excType) { \
    bool exceptionThrown = false;\
    try { \
        expr; \
    } catch (const excType&) { \
        exceptionThrown = true; \
    } catch (...) { \
        exceptionThrown = false; \
    } \
    if (!exceptionThrown) { \
        std::ostringstream oss; \
        oss << "Expected exception of type " << typeid(excType).name() << " but no exception was thrown"; \
        throw std::runtime_error(oss.str()); \
    } \
}
