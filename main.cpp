
#include "tokenize_parse.h"
#include "get_artistid.h"
#include "genres.h"
#include "get_trackid.h"
#include "get_audiofeatures.h"
#include <cpr/cpr.h>

//token from spotify.
const string TOKEN = " ";

//function def
void callAPI_artistname(string artistName);

//comparing mechanism demo.
class Profile {
public:
    //acoustic, energy, instrumentals
    float feature_1;
    float dancebility;
    float loudness;
    int mode;
    float tempo;
    float valence;
    float popularity;
    string genre;
    Profile(float a, float b, float c, int d, float e, float f, float g, string h) :
        feature_1(a), dancebility(b), loudness(c), mode(d), tempo(e), valence(f), popularity(), genre(h) {}
};

float comparing_feature(float x, float y) {
    return ((1 - (x - y)) * 6);
}

float comparing_dancebility(float x, float y) {
    return ((1 - (x - y)) * 8);
}

float comparing_loudness(float x, float y) {
    return (((30 - (x - y)) / 30) * 6);
}
int comparing_mode(int x, int y) {
    if (x == y) return 6;
    else return 1;
}

float comparing_tempo(float x, float y) {
    return (((200 - (x - y)) / 200) * 6);
}

float comparing_valence(float x, float y) {
    return ((1 - (x - y)) * 10);
}

float comparing_popularity(float x, float y) {
    return (((100 - (x - y)) / 100) * 6);
}

int comparing_genre(string genre1, string genre2) {
    //exits the function if the whole string matches.
    // eg : "indie folk" == "indie folk"
    int x=0;
    if (genre1 == genre2) {
        return 10;
    }
    else {

        vector<string> token1;
        vector<string> token2;
        tokenize(genre1, ' ', token1);
        tokenize(genre2, ' ', token2);

        //compares a word
        for (int i = 0; i < token1.size(); i++) {
            for (int j = 0; j < token2.size(); j++) {
                if (token1[i] == token2[j]) {
                    x += 5;
                }
            }
        }
        return x;
    }

}

//call a new api with returned unique id.
void callAPI_GENRE(string artist_id) {

    string URI = "https://api.spotify.com/v1/artists/"; 
    URI = URI + artist_id;
    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    cout << '\n' << "NOW AGAIN, REQUESTING API FOR GENRES WITH THE RETRIEVED UNIQUE ARTIST ID." << '\n';

    switch (r.status_code) {
    case 200:
        cout << "THE API REQUEST WAS SUCEEDED." << endl;
        break;
    case 400:
        cout << "INVALID REQUEST." << endl;
        break;
    case 404:
        cout << "THE TOKEN HAS EXPIRED." << endl;
        break;
    case 429:
        cout << "Too Many Requests - Rate limiting has been applied by the SPOTIFY SERVER." << endl;
        break;
    }

    auto genres = getgenres(r.text);
    for (auto x : genres) {
        cout << x << endl; 
    }
}

//call api for audio features.(1st question)
void callAPI_audiofeatures(string track_id){
    string URI = "https://api.spotify.com/v1/audio-features/";
    URI += track_id;
    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    cout<<'\n' << '\n' << "Again, calling an api request for AUDIO FEATURES using retreived unique track id." <<endl;

    switch (r.status_code) {
    case 200:
        cout << "THE REQUEST WAS SUCEEDED." << endl;
        break;
    case 400:
        cout << "INVALID REQUEST." << endl;
        break;
    case 404:
        cout << "THE TOKEN HAS EXPIRED." << endl;
        break;
    case 429:
        cout << "Too Many Requests - Rate limiting has been applied by the SPOTIFY SERVER." << endl;
        break;
    }
    
    //Now getting a feature.
    string feature[10] = { "danceability", 
        "energy", 
        "loudness", 
        "mode", 
        "speechiness",
        "acousticness",
        "instrumentalness",
        "liveness",
        "valence",
        "tempo" };
    for (int i = 0; i < 10; i++) {
        string parameter = get_audiofeatures(r.text, feature[i]);
        cout << "the " << feature[i] << " of the track is: " << parse(parameter) << endl;
    }
    }

//call api with inputed track name. [af bhanya audio features.]
void callAPI_trackname_af(string trackname, string artistname) {
    string URI = "https://api.spotify.com/v1/search?q=";
    URI += parse(trackname);
    URI += parse(artistname);
    URI += "&type=track&limit=1";

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    cout << "\n" << "TRACK INFO:" << endl;
    cout << "calling an api request to retrieve track id." << endl;

    switch (r.status_code) {
    case 200:
        cout << "THE API REQUEST WAS SUCEEDED." << endl;
        break;
    case 400:
        cout << "INVALID REQUEST." << endl;
        break;
    case 404:
        cout << "INVALID REQUEST." << endl;
        break;
    case 401:
        cout << "THE TOKEN HAS EXPIRED." << endl;
        break;
    case 429:
        cout << "Too Many Requests - Rate limiting has been applied by the SPOTIFY SERVER." << endl;
        break;
    }
    string track_id = parse(get_trackid(r.text));
    cout << "the track id is: "<< track_id;

    callAPI_audiofeatures(track_id);
    cout << "\n";
    callAPI_artistname(artistname);
}

//call spotify api with trackname and artist name (3rd question)
void callAPI_artistname(string artistName) {

    string URI = "https://api.spotify.com/v1/search?q=";
    URI = URI + parse(artistName);
    URI = URI + "&type=artist&limit=1";

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    cout << "\n" << "ARTIST INFO:" << endl;
    cout << "calling an api request to retrieve artist id." << '\n';
    
    switch (r.status_code) {
    case 200:
        cout << "THE REQUEST WAS SUCEEDED." << endl;
        break;
    case 400:
        cout << "INVALID REQUEST." << endl;
        break;
    case 404:
        cout << "THE TOKEN HAS EXPIRED." << endl;
        break;
    case 429:
        cout << "Too Many Requests - Rate limiting has been applied by the SPOTIFY SERVER." << endl;
        break;
    }
    string artist_id = getartistid(r.text);
    cout << "THE ARTIST ID IS: " << artist_id<<endl;
    callAPI_GENRE(artist_id);
}


int main(int argc, char** argv) {
    cout << "Testing..." << endl;
    string trackName;
    string artistName;
    
    cout << "\n" << "\"FIRST QUESTION\"" << endl;
    cout << "NAME A SONG YOU'VE OVERPLAYED LIKE 1000 TIMES:" << endl;
    cout << "the song name:" << endl;
    getline(cin, trackName);
    cout << "the song's artist name:" << endl;
    getline(cin, artistName);
    callAPI_trackname_af(trackName, artistName);
    
    cout << "\n" << "\"SECOND QUESTION\"" << endl;
    cout << "NAME A SONG THAT DEFINES YOU AS A PERSON:" << endl;
    cout << "the song name:" << endl;
    getline(cin, trackName);
    cout << "the song's artist name:" << endl;
    getline(cin, artistName);
    callAPI_artistname(artistName);
    
    cout << "\n" << "\"THIRD QUESTION\"" << endl;
    cout << "NAME YOUR FAVOURITE ARTIST:" << endl;
    cout << "the artist name:" << endl;
    getline(cin, artistName);
    callAPI_artistname(artistName);

    //Genre_Matchup();
    
    //comparing mechanism demo.
    /*Profile P1(0.765, 0.395, -9.72, 1, 168.924, 0.338, 86, "modern rap");
    Profile P2(0.843, 0.637, -11.851, 1, 123.992, 0.315, 47, "modern pop");
    float feature_per = comparing_feature(P1.feature_1,P2.feature_1);
    float dancebility_per = comparing_dancebility(P1.dancebility,P2.dancebility);
    float loudness_per = comparing_loudness(P1.loudness,P2.loudness);
    int mode_per = comparing_mode(P1.mode,P2.mode);
    float tempo_per = comparing_tempo(P1.tempo,P2.tempo);
    float valence_per = comparing_valence(P1.valence, P2.valence);
    float popularity_per = comparing_popularity(P1.popularity,P2.popularity);
    int genre_per = comparing_genre(P1.genre, P2.genre);
    float total_match_per = feature_per + dancebility_per + loudness_per + mode_per + tempo_per + valence_per + valence_per + popularity_per + genre_per;
    cout<< "The match percentage between Profile 1 and Profile 2 is "<<total_match_per<<"%." << endl;
    */ 

    return 0;
}
