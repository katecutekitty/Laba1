#pragma once
#include <exception>
#include <string>
#include "utils.h"

using namespace std;

class InvalidStringFormatException : public exception {
private:
    string errorMessage;

public:
    explicit InvalidStringFormatException(const string& message)
        : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

