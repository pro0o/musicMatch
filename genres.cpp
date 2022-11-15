#include "genres.h"

vector<string> getgenres(string response) {
    cout << "getting genders:" << endl;

    vector<string> tokens;
    string to_find = "genres";

    //found -> position of "g" of "genre" in response.
    size_t found = response.find(to_find);

    //skip "genres : ["
    found += 12;

    //setting _genres string empty.
    string _genres = "";

    //for loop untill genres end with ]
    for (; response[found] != ']'; found++) {
        _genres += response[found];
    }

    //removing commas.
    tokenize(_genres, ',', tokens);
    const char comma = ',';

    //initialize genre result as vector.
    vector<string> result;

    //repalce " with ''.
    for (auto x : tokens) {
        string temp = "";
        for (auto ch : x) {
            if (ch == '"')
                continue;
            temp += ch;
        }
        //remove whitespace in first place if it exists
        if (temp[0] == ' ')
            temp.erase(0, 1);
        result.push_back(temp);
    }

    return result;
}


void Genre_Matchup() {
    string genre1 = "modern rap";
    string genre2 = "underground rap";


    //exits the function if the whole string matches.
    // eg : "indie folk" == "indie folk"

    if (genre1 == genre2) {
        cout << "10%" << endl;
        return;
    }


    vector<string> token1;
    vector<string> token2;
    tokenize(genre1, ' ', token1);
    tokenize(genre2, ' ', token2);


    //compares a word
    for (int i = 0; i < token1.size(); i++) {
        for (int j = 0; j < token2.size(); j++) {
            if (token1[i] == token2[j]) {
                cout << "5%" << endl;
                break;
            }
        }
    }
}