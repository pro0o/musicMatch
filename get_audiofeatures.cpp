#include "get_audiofeatures.h"

//get the features of the track.
string get_audiofeatures(string response, string feature) {
    vector<string> tokens;
    tokenize(response, '"', tokens);
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == feature) {
            return tokens[i + 1];
        }
    }
}
