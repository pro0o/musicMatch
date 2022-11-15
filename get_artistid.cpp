#include "get_artistid.h"

//get artist id
string getartistid(string response) {
    vector<string> tokens;
    tokenize(response, '"', tokens);

    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "id") {
            return tokens[i + 2];
        }
    }
}
