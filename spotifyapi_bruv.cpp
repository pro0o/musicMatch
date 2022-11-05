#include <cpr/cpr.h>
#include <iostream>
#include <string>

using namespace std;

string parseName(string trackName, string artistName) {
    //replace whitespace with '+'.
    string _temp;
    for (auto x : trackName) {
        if (x == ' ')_temp+='+';
        else _temp += x;
    }
    _temp += ',';
    for (auto x : artistName) {
        if (x == ' ')_temp += '+';
        else _temp += x;
    }
    return _temp;
}

void getTrackID(string trackName, string artistName) {
    //spotify api link
    string URI = "https://api.spotify.com/v1/search?q=";
    URI += parseName(trackName, artistName);
    URI += "&type=track&limit=1";
    //authorization token from postman
    string TOKEN = "BQC-SquZA1KsdNI1rAwrS7MLFUXgP-ACL-gbUee0-EzI88Fd0Zd_IAmc62OkW73RctHcdGDJedR13ZhlIo_nZMsn80LFxMrzRdBk01b82BXk-N21UThPvGcY2uxCTiD2oucgkkg_8ltleo4PDmN809hPJsVMNGnKKRkNnEUG4Wog5js5y5I7ozdjRC0kfVnjAUbNYAVrb8CzK8DuK6JE6Gw5c92htgabR-46ZBwL1AN_MNv43w6UNKofQLHyw6uMbQRkpGTkEQ";

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });

    cout << "Status code: " << r.status_code << '\n';
    cout << r.text << endl;
}

int main(int argc, char** argv) {
    /*
    std::string URI = "https://api.spotify.com/v1/artists/0TnOYISbd1XYRBk9myaseg";
    std::string TOKEN = "BQBAJ2nfeZJ1Aejs5XVJnonNW62hZnl4XQm6o-CvfDpiAbm1qWOsffjbUoGqh--yQDewMJ18zoDPphXjnLIqGCHuMYc47jNxCCSrZ85s1DbJZy2XNr17DVeow-MotpCYLcTJsCOAtEL3UHIRWesinU19cRl6cwV3z0mFH8DF2UZFSoBLlsRUmx0b7dW5Dl_B6FwkoItrbgQqnGLM2ZACL7jPFWBQjNA0oKQFE4JWGIl4i_B1PoBV33I5d9guu3WINyLp_eYGYA";

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{TOKEN});
    
    std::cout << "Status code: " << r.status_code << '\n';
    */

    cout << "Testing...." << std::endl;
    //song and artist name
    string name = "hope";
    string artist = "meat computer";
    getTrackID(name, artist);

    return 0;
}
