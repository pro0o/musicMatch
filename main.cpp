#include "tokenize_parse.h"
#include "get_artistid.h"
#include "genres.h"
#include "get_trackid.h"
#include "get_audiofeatures.h"
#include <cpr/cpr.h>
#include "sqlite/sqlite3.h"
using namespace std;

sqlite3* db;
sqlite3_stmt* stmt;
string Profile_Name = "chodu bhai";

//token from spotify.
const string TOKEN = "BQCsJHpVpZgGrGntL6V2hBgNDgmX-5McXaTMdL3ovsUb90i6abKJyuFjx52bRJhMeXNrcsL1FT7u3RS7XImCdk6REs6U58N4DroU5aLOIcCQCM1NYUl2y3mgb2N61kP0EyBE9ydZhy__3QxReeBxr-wc0GncGrzKoLHlv0m7L4fzrQ-bF2CIfozj0Oyfn1RmfebEnLPyvE5D_x_j49JUz9n2u4tEfIImAStn8GgTKaOfukrR4MqQVqFkKkZR0rn5B99mzUHPrA";

//function def.
string callAPI_artist_name(string artistName);

void connection() {
    if (sqlite3_open("demo.db", &db) == SQLITE_OK) {

        string query_1 = "CREATE TABLE IF NOT EXISTS music_match(Profile_Name VARCHAR(10), Acoustic DOUBLE, Danceability DOUBLE, Energy DOUBLE, Key INT, Speechiness DOUBLE, Mode INT, Tempo DOUBLE, Valence DOUBLE, Liveness DOUBLE, Genres VARCHAR(100));";
        int response = sqlite3_prepare_v2(db, query_1.c_str(), -1, &stmt, NULL);
        //declare the statement.
        sqlite3_step(stmt);
        //delete the statement.
        sqlite3_finalize(stmt);
        if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
        else cout << "TABLE WAS CREATED SUCCESSFULLY." << endl;

    }
}

//adding audio features and genres into a row(PROFILE).
void adding_up(string Profile_Name, double Acoustic, double Danceability, double Energy, int Key, double Speechiness, int Mode, double Tempo, double Valence, double Liveness, string genres) {
    if (sqlite3_open("demo.db", &db) == SQLITE_OK) {
        string query_2 = "INSERT INTO music_match(Profile_Name, Acoustic, Danceability, Energy, Key, Speechiness, Mode, Tempo, Valence, Liveness, Genres) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
        int response = sqlite3_prepare_v2(db, query_2.c_str(), -1, &stmt, NULL);
        sqlite3_bind_text(stmt, 1, Profile_Name.c_str(), Profile_Name.length(), SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 2, Acoustic);
        sqlite3_bind_double(stmt, 3, Danceability);
        sqlite3_bind_double(stmt, 4, Energy);
        sqlite3_bind_int(stmt, 5, Key);
        sqlite3_bind_double(stmt, 6, Speechiness);
        sqlite3_bind_int(stmt, 7, Mode);
        sqlite3_bind_double(stmt, 8, Tempo);
        sqlite3_bind_double(stmt, 9, Valence); 
        sqlite3_bind_double(stmt, 10, Liveness);
        sqlite3_bind_text(stmt, 11, genres.c_str(), genres.length(), SQLITE_TRANSIENT);

        //declare the statement.
        sqlite3_step(stmt);
        //delete the statement.
        sqlite3_finalize(stmt);
        if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
        else cout << "AUDIO FEATURES WERE ADDED SUCCESSFULLY." << endl;
    }
}

/*void read_data() {
    //instead of * a column head name can be specified like name, roll, email.
    //string query_3 = "SELECT * FROM user";
    string query_3 = "SELECT rowid, * FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //while looop until the the last row of name column.
    else while (response = sqlite3_step(stmt) == SQLITE_ROW) {
        cout << sqlite3_column_text(stmt, 0) << "\t" << sqlite3_column_text(stmt, 1) << "  " << sqlite3_column_text(stmt, 2)
            << "  " << sqlite3_column_text(stmt, 3) << endl;
    }
}

void delete_shit() {
    int roll = 47;
    string query_3 = "DELETE FROM user WHERE roll = ?";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, roll);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (response != SQLITE_OK) cout << "ERROR:" << sqlite3_errmsg(db) << endl;
    else cout << "DATAS WERE DELETED SUCCESSFULLY FROM ROLL NO: " << roll << endl;
}


void update_shit() {
    int roll = 47;
    string name = "lavde";
    string query_3 = "UPDATE user SET name = ? WHERE roll = ?";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (response != SQLITE_OK) cout << "ERROR:" << sqlite3_errmsg(db) << endl;
    else cout << "DATAS WERE UPDATED SUCCESSFULLY FROM ROLL NO: " << roll << endl;
}

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
*/
//call a new api with returned unique id.
string callAPI_GENRE(string artist_id) {

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
    string genres = getgenres(r.text);
    return genres;
}

//call api for audio features.(1st question)
void callAPI_audiofeatures(string track_id, string artistname){
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
    
    //Now getting features.
    string feature[9] = {"acousticness", "danceability", "energy", "key", "speechiness", "mode", "tempo", "valence", "liveness"};
    double feature_af[9]= {};
    int mode = 0;
    int key = 0;
    for (int i = 0; i < 9; i++) {
        if(i == 3) {
            string parameter = get_audiofeatures(r.text, feature[i]);
            //convert string into int.
            key = stoi(parse(parameter));            
            cout << "the key of the song is:" << key << endl;
        }
        else if(i == 5) {
            string parameter = get_audiofeatures(r.text, feature[i]);
            //convert string into int.
            mode = stoi(parse(parameter));
            cout << "the mode of the song is:" << mode << endl;
        }
        else {
            string parameter = get_audiofeatures(r.text, feature[i]);
            //convert string into double.
            feature_af[i] = stod(parse(parameter));
            cout << "the "<<feature[i] <<" of the song is : " << feature_af[i] << endl;
        }
    }
    string artist_id = callAPI_artist_name(artistname);
    string genres = callAPI_GENRE(artist_id);
    connection();
    adding_up(Profile_Name, feature_af[0], feature_af[1], feature_af[2], key, feature_af[4], mode, feature_af[6], feature_af[7], feature_af[8], genres);
}

//call api with inputed track name.
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
    callAPI_audiofeatures(track_id, artistname);
}

//call spotify api with trackname and artist name (3rd question)
string callAPI_artist_name(string artistName) {

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
    return artist_id;
}

void comparison_demo() {
    int rowid = 1;
    string query_3 = "SELECT rowid, * FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //while looop until the the last row of name column.
    else while (response = sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* genres = sqlite3_column_text(stmt, 11);
        string _genres = reinterpret_cast<const char*>(genres);
        cout << _genres;
        break;
    }

    /*string genre_1 = "hip hop\nlgbtq+ hip hop\nneo soul\npop";
    cout<<"genre of profile 1:\n" << genre_1 <<endl;
    string genre_2 = "conscious hip hop\nhip hop\nrap\nwest coast rap";
    cout<<"\n" << "genre of profile 2:\n" << genre_2  << endl;
    
    cout << "\n" << "COMPARING SHIT..." << endl;
    string a;
    //creating an array of first profile genres.
    int count_1 = 0;
    string genre_array_1[10] = {};
    for (int i = 0; i < genre_1.size() + 1; i++) {
        if (genre_1[i] == '\n' || genre_1[i] == genre_1[genre_1.size()]) {
            count_1++;
            genre_array_1[count_1 - 1] = a;
            a.erase(0, a.size());
        }
        else a += genre_1[i];
    }
    //creating an array of second profile genres.
    //new line counts. 
    int count_2 = 0;
    string genre_array_2[10] = {};
    for (int i=0; i < genre_2.size()+1; i++) {
        if (genre_2[i] == '\n' || genre_2[i]==genre_2[genre_2.size()]) {
            count_2++;
            genre_array_2[count_2 - 1] = a;
            a.erase(0, a.size());
        }
        else a+= genre_2[i];
    }*/
}


int main(int argc, char** argv) {
    cout << "Testing..." << endl;
    string trackName="birthday";
    string artistName="gia margaret";
    
    cout << "\n" << "\"FIRST QUESTION\"" << endl;
    //cout << "NAME A SONG YOU'VE OVERPLAYED LIKE 1000 TIMES:" << endl;
    //cout << "the song name:" << endl;
    //getline(cin, trackName);
    //cout << "the song's artist name:" << endl;
    //getline(cin, artistName);
    //callAPI_trackname_af(trackName, artistName);
    /*
    cout << "\n" << "\"SECOND QUESTION\"" << endl;
    cout << "NAME A SONG THAT DEFINES YOU AS A PERSON:" << endl;
    cout << "the song name:" << endl;
    getline(cin, trackName);
    cout << "the song's artist name:" << endl;
    getline(cin, artistName);
    callAPI_artistname(artistName);
    */
    //cout << "\n" << "\"THIRD QUESTION\"" << endl;
    //cout << "NAME YOUR FAVOURITE ARTIST:" << endl;
    //cout << "the artist name:" << endl;
    //getline(cin, artistName);
    //callAPI_artistname(artistName);

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
    //comparison_demo();
    

    //first creating a base for user table.
    connection();
    comparison_demo();
    //delete_shit();
    //update_shit();
    sqlite3_close(db);

    return 0;
}
