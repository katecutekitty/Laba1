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