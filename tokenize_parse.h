#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string parseName(string artistName);
void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);