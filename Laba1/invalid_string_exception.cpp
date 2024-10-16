#include "invalid_string_exception.h"
#include <iostream>
#pragma once;

using namespace std;

class InvalidStringException : public exception {
	public:
		InvalidStringException(const char* message) {

		}
};
