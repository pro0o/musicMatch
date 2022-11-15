#include "tokenize_parse.h"

//change whitespace with +.
string parseName(string artistName) {
    string _temp;
    _temp += ',';
    for (auto x : artistName) {
        if (x == ' ')_temp += '+';
        else _temp += x;
    }
    return _temp;
}

void tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    //getline funciton: to read a string or a line from an input stream.
    while (getline(ss, s, delim)) {
        //pushback function: to insert data or elements at the end of a vector or it pushes the element in the vector from the back.
        out.push_back(s);
    }
}

