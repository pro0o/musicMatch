/*
#include "get_artistid.h"

//get artist id
std::string getartistid(std::string response) {
    std::vector<std::string> tokens;
    tokenize(response, '"', tokens);
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "id") {
            return tokens[i + 2];
        }
    }
}
*/
