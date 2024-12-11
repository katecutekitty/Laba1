#ifndef UTILSH

#include <string>
#include <chrono>
#include <vector>

using namespace std;

pair<chrono::hours, chrono::minutes> makeTimeFromString(string t);

vector<string> divideStringIntoParameters(string s);

vector<string> readFromFile(string filePath);

void validateArgs(const vector<string>& args, int lastParam);

#endif 