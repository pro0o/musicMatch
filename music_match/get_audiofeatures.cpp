/*#include "get_audiofeatures.h"

//get the features of the track.
std::string get_audiofeatures(std::string response, std::string feature) {
    std::vector<std::string> tokens;
    tokenize(response, '"', tokens);
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == feature) {
            return tokens[i + 1];
        }
    }
}
*/
