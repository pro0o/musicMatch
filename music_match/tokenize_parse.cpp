/*#include "tokenize_parse.h"

//remove shit.
std::string parse(std::string id) {
    std::string _temp;
    for (auto x : id) {
        if (x == ',' || x == '"' || x == '\n' || x == ':' || x == ' ')_temp += "";
        else _temp += x;
    }
    return _temp;
}
std::string parse_shit(std::string id) {
    std::string _temp;
    for (auto x : id) {
        if (x == ' ')_temp += "+";
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
*/
