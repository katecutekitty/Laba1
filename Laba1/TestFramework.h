#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>

class TestFramework {
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

private:
    static std::vector<std::pair<std::string, std::function<void()>>>& getTests() {
        static std::vector<std::pair<std::string, std::function<void()>>> tests;
        return tests;
    }
};

#define TEST(name) void name(); \
    static const bool name##_registered = \
        (TestFramework::registerTest(#name, name), true); \
    void name()

#define ASSERT_TRUE(condition) TestFramework::assertTrue(condition, #condition " failed")
#define ASSERT_EQ(expected, actual) TestFramework::assertEqual((expected), (actual), "Assertion failed")
