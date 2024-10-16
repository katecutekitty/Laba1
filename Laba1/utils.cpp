#include <string>
#include <chrono>
#include <string>
#include "utils.h"
#pragma once;

using namespace std;

pair<chrono::hours, chrono::minutes> makeTimeFromString(string t) {
    string minStr, hrStr;
    pair<chrono::hours, chrono::minutes> time;
    hrStr = t.substr(0, t.find(':'));
    minStr = t.substr(t.find(':') + 1);
    time = make_pair(chrono::hours{ stoi(hrStr) }, chrono::minutes{ stoi(minStr) });
    return time;
}
bool checkString(string s) {

}

vector<string> divideStringIntoParameters(string input) {
    vector<string> args(4);
    args[0] = input.substr(1, input.find(';') - 2);
    input = input.substr(input.find(';') + 1);
    args[1] = input.substr(0, input.find(';'));
    args[2] = input.substr(input.find(';') + 1);

    return args;
}