#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string parse(string);
string parse_shit(string id);
string parse_empty(string);
void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);