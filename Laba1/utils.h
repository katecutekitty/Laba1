#ifndef UTILSH

#include <string>
#include <chrono>
#include <vector>

using namespace std;

pair<chrono::hours, chrono::minutes> makeTimeFromString(string t);

bool checkString(string s);

vector<string> divideStringIntoParameters(string s);

vector<string> readFromFile(string filePath);

#endif 