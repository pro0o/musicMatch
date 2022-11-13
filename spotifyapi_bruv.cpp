#include <cpr/cpr.h>
#include <iostream>
#include <string>

using namespace std;

//token from postman.
const string TOKEN = "BQBBli_sTyGRnbd660qx9wvjBeMzKJJR3HnzVPm5HBYT4mLXZV8a-NcdkP0G5qSXAAM0Du7112lO0M6VQkI_XsGQrF3SBKM_ytrO8aDSr7l7gPMWQ9PkmSe0ea1w1QyCNFNk2iXJscUkgkrdEVYhZUduADnvIWQWvZjytA4rOx29PfqmfcXVnKYRpfB6f9s3mIP3mq5kGcXMpZ2CrVTv-BaqWc_EEG5f1CmoN8rpeujCbAatIoatvnrsQ6bei9JPpyAGc5Le_g";

//definitions
string getartistid(string);
void callAPI_withID(string);
void getgenres(string);

//replace whitespace with +.
string parseName(string trackName, string artistName) {
    string _temp;
    for (auto x : trackName) {
        if (x == ' ')_temp += '+';
        else _temp += x;
    }
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
    while (std::getline(ss, s, delim)) {
        //pushback function: to insert data or elements at the end of a vector or it pushes the element in the vector from the back.
        out.push_back(s);
    }
}

//call spotify api with trackname and artist name (1st question)
void callAPI(string trackName, string artistName) {
    
    string URI = "https://api.spotify.com/v1/search?q=";
    URI += parseName(trackName, artistName);
    URI += "&type=track&limit=1";

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });

    cout << "Status code: " << r.status_code << '\n';
    cout << r.text;
    string id = getartistid(r.text);
    callAPI_withID(id);
}

//get artist id
string getartistid(string response) {
    vector<string> tokens;
    string id;
    const char delim = ' ';
    tokenize(response, delim, tokens);
    string a = "";
    string artistid = "";
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "\"id\"") {
            id = tokens[i + 2];
            //replace " with no space.
            for (auto x : id) {
                if (x == '"' or x == ',') artistid += a;
                else artistid += x;
            }
            break;
        }
    }
    cout << artistid;
    return artistid;
}

//call a new api with returned unique id.
void callAPI_withID(string id) {

    string URI = "https://api.spotify.com/v1/artists/";
    URI += id ;

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    cout << "Status code: " << r.status_code << '\n';
    cout << r.text;
}

//get genres.
void getgenres(string response) {
    string gen;
    const char delim = ' ';
    std::vector<std::string> token;
    tokenize(response, delim, token);
    string genre = "";
    for (int i = 0; i < token.size(); i++) {
        if (token[i] == "\"genre\"") {
            gen = token[i + 2] + " " + token[i + 3] + " " + token[i + 4];
            for (auto x : gen) {
                if (x == '"' or x == ',') genre += ' ';
                else genre += x;
            }
            break;
        }
    }
    cout << genre;
}

int main(int argc, char** argv) {
    cout << "Testing...." << std::endl;
    string name = "elsewhere";
    string artist = "eden";
    callAPI(name, artist);
    return 0;
}
