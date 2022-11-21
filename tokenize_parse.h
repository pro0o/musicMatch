#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string parse(string);
void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);
