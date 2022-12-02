#include "tokenize_parse.h"
#include "get_artistid.h"
#include "genres.h"
#include "get_trackid.h"
#include "get_audiofeatures.h"
#include "sqlite/sqlite3.h"
#include <set>
#include <cpr/cpr.h>
#include <iostream>

using namespace std;

string _Genres;
int row_id;
int name_check=12;
vector <string> Profile_names(name_check);

sqlite3* db;
sqlite3_stmt* stmt;

//functions def
void callAPI_artist_name(string artistName);

//token from spotify.
const string TOKEN = "BQAcy8mIj9e1RfREU_nHg8I-xxqPdSC_ccmjmBCBEijuDrUBMCNQQQQf95jlGe8j02lm7OHc7bsNILSgxPDnmDbywVmEd67ulyKxB_rYCi5KeYX1SvSdDrrUgJSL4cCEA1DubzB30zJkQv_yRvoG8rgffr_2l8RyWtV1afAuFWpOfXy41sZG26GS9z0";

//global variables.
double feature_af[9] = {};


//connecting to database.
void connection() {
    if (sqlite3_open("demo1.db", &db) == SQLITE_OK) {
        string query_1 = "CREATE TABLE IF NOT EXISTS music_match(row_id INT, Profile_Name VARCHAR(10), Acoustic DOUBLE, Danceability DOUBLE, Energy DOUBLE, Key INT, Speechiness DOUBLE, Mode INT, Tempo DOUBLE, Valence DOUBLE, Liveness DOUBLE, Genres VARCHAR(100));";
        int response = sqlite3_prepare_v2(db, query_1.c_str(), -1, &stmt, NULL);
        //declare the statement.
        sqlite3_step(stmt);
        //delete the statement.
        sqlite3_finalize(stmt);
        if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
        else cout << "TABLE WAS CREATED SUCCESSFULLY." << endl;

    }
}

void userProfile_check() {
    //selecting Profile_Name column from table.
    string query_3 = "SELECT Profile_Name FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        Profile_names[i] = _genres;
    }
}

/*
void update_shit(string Profile_Name, double Acoustic, double Danceability, double Energy, int Key, double Speechiness, int Mode, double Tempo, double Valence, double Liveness, string genres) {
    string username = Profile_Name;
    string query_3 = "UPDATE music_match SET Profile_Name = ?, Acoustic= ?, Danceability = ?, Energy = ?, Key = ?, Speechiness = ?, Mode = ?, Tempo = ?, Valence = ?, Liveness = ?, genres =? WHERE row_id = 0;";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
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
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (response != SQLITE_OK) cout << "ERROR:" << sqlite3_errmsg(db) << endl;
    else cout << "DATAS WERE UPDATED SUCCESSFULLY FROM Profile:"<<Profile_Name <<  endl;
}
*/

//adding audio features and genres into a row(PROFILE).
/*void adding_up(int row_id, string Profile_Name, double Acoustic, double Danceability, double Energy, int Key, double Speechiness, int Mode, double Tempo, double Valence, double Liveness, string genres) {
    if (sqlite3_open("demo1.db", &db) == SQLITE_OK) {
        string query_2 = "INSERT INTO music_match(row_id, Profile_Name, Acoustic, Danceability, Energy, Key, Speechiness, Mode, Tempo, Valence, Liveness, Genres) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
        int response = sqlite3_prepare_v2(db, query_2.c_str(), -1, &stmt, NULL);
        row_id += 1;
        sqlite3_bind_int(stmt, 1, row_id);
        sqlite3_bind_text(stmt, 2, Profile_Name.c_str(), Profile_Name.length(), SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 3, Acoustic);
        sqlite3_bind_double(stmt, 4, Danceability);
        sqlite3_bind_double(stmt, 5, Energy);
        sqlite3_bind_int(stmt, 6, Key);
        sqlite3_bind_double(stmt, 7, Speechiness);
        sqlite3_bind_int(stmt, 8, Mode);
        sqlite3_bind_double(stmt, 9, Tempo);
        sqlite3_bind_double(stmt, 10, Valence);
        sqlite3_bind_double(stmt, 11, Liveness);
        sqlite3_bind_text(stmt, 12, genres.c_str(), genres.length(), SQLITE_TRANSIENT);

        //declare the statement.
        sqlite3_step(stmt);
        //delete the statement.
        sqlite3_finalize(stmt);
        if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
        else
            cout << "NEW PROFILE WAS ADDED SUCCESSFULLY." << endl;
    }
}
*/

void adding_up(int row_id, string Profile_Name, double Acoustic, double Danceability, double Energy, int Key, double Speechiness, int Mode, double Tempo, double Valence, double Liveness, string genres) {
    string insertQuery = "INSERT INTO music_match(row_id, Profile_Name, Acoustic, Danceability, Energy, Key, Speechiness, Mode, Tempo, Valence, Liveness, Genres) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
        sqlite3_stmt * insertStmt;
    sqlite3_prepare(db, insertQuery.c_str(), insertQuery.size(), &insertStmt, NULL);
    sqlite3_bind_int(insertStmt, 1, row_id);
    sqlite3_bind_text(insertStmt, 2, Profile_Name.c_str(), Profile_Name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_double(insertStmt, 3, Acoustic);
    sqlite3_bind_double(insertStmt, 4, Danceability);
    sqlite3_bind_double(insertStmt, 5, Energy);
    sqlite3_bind_int(insertStmt, 6, Key);
    sqlite3_bind_double(insertStmt, 7, Speechiness);
    sqlite3_bind_int(insertStmt, 8, Mode);
    sqlite3_bind_double(insertStmt, 9, Tempo);
    sqlite3_bind_double(insertStmt, 10, Valence);
    sqlite3_bind_double(insertStmt, 11, Liveness);
    sqlite3_bind_text(insertStmt, 12, genres.c_str(), genres.length(), SQLITE_TRANSIENT);

    if (sqlite3_step(insertStmt) != SQLITE_DONE) cout << "Didn't Insert Item!" << endl;
    else cout << "Your profiles was successfully added."<<endl;
}

/*
void delete_shit() {
    int roll = 47;
    string query_3 = "DELETE FROM user WHERE roll = ?";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, roll);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (response != SQLITE_OK) cout << "ERROR:" << sqlite3_errmsg(db) << endl;
    else cout << "DATAS WERE DELETED SUCCESSFULLY FROM ROLL NO: " << roll << endl;
    _count--;
}
*/


//call api for audio features.
void callAPI_audiofeatures(string track_id, string artistname) {
    string URI = "https://api.spotify.com/v1/audio-features/";
    URI += track_id;
    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    cout << '\n' << '\n' << "Again, calling an api request for AUDIO FEATURES using retreived unique track id." << endl;

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
    string feature[9] = { "acousticness", "danceability", "energy", "key", "speechiness", "mode", "tempo", "valence", "liveness" };
    for (int i = 0; i < 9; i++) {
        string parameter = get_audiofeatures(r.text, feature[i]);
        //convert string into double.
        feature_af[i] = stod(parse(parameter));
        cout << "the " << feature[i] << " of the song is : " << feature_af[i] << endl;
    }
}

void callAPI_GENRE(string artist_id) {

    string URI = "https://api.spotify.com/v1/artists/";
    URI = URI + artist_id;
    cout << URI;
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

    //check if the same genre exists or not...
    if (_Genres == "")_Genres += genres;
    
    else {
        //a is a temp string.
        string a;
        //creating an array that stores separate genre distinguished by newline.

        //ffs count_1/count_2 important affffff.
        //count_1/count_2 increases by 1 if any new line or last element is met and later on determines the size of array with genres filled.
        int count_1 = 0;
        string genre_array_1[20] = {};
        //if a character is new line or last element of string, then count is added by 1 and until new line string is added in array.
        for (int i = 0; i <= _Genres.size(); i++) {
            if (_Genres[i] == '\n' || _Genres[i] == _Genres[_Genres.size()]) {
                count_1++;
                if (a.back() == ' ') {
                    a.pop_back();
                    genre_array_1[count_1 - 1] = a;
                }
                else genre_array_1[count_1 - 1] = a;
                a.erase(0, a.size());
            }
            //adding up characters in a from genre string.
            else a += _Genres[i];

        }

        cout << "\n" << count_1 << " datas were stored in genres array:" << endl;
        for (int i = 0; i < count_1; i++) {
            cout << i << " " << genre_array_1[i] << endl;
        }

        string genre_array_2[20] = {};
        int count_2 = 0;
        for (int i = 0; i <= genres.size(); i++) {
            if (genres[i] == '\n' || genres[i] == genres[genres.size()]) {
                count_2++;
                if (a.back() == ' ') {
                    a.pop_back();
                    genre_array_2[count_2 - 1] = a;
                }
                else genre_array_2[count_2 - 1] = a;
                a.erase(0, a.size());
            }
            else a += genres[i];
        }

        std::cout << count_2 << " datas were stored in genre 1 array:" << endl;
        for (int i = 0; i < count_2; i++) {
            cout << i << " " << genre_array_2[i] << endl;
        }
        //setting up set to make a union of elements of two arrays.
        std::set < std::string> s;
        // inserting elements in set.
        for (int i = 0; i < count_1; i++) {
            if(genre_array_1[i] != " ")
            s.insert(genre_array_1[i]);
        }
        for (int i = 0; i < count_2; i++) {
            if (genre_array_2[i] != " ")
            s.insert(genre_array_2[i]);
        }

        // printing set s
        //initialising the iterator, iterating to the beginning of the set.
        std::set <std::string >::iterator it;
        //remove _Genre string so that before genres doesnt get mixed up.
        _Genres.erase();
        for (it = s.begin(); it != s.end(); it++)
        {   
            cout << *it<<"+";
            _Genres += *it + "\n";
        }
        //remove end new line.
        _Genres.pop_back();
        std::cout << "The element of set s are :" << std::endl;
        std::cout << _Genres << std::endl;
        std::cout << "genres stored in this session are:" << _Genres << std::endl;
    }
}

//call spotify api with trackname and artist name (3rd question)
void callAPI_artist_name(string artistName) {

    string URI = "https://api.spotify.com/v1/search?q=";
    URI = URI + parse_shit(artistName);
    URI = URI + "&type=artist&limit=1";
    cout << URI;

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
    cout << "THE ARTIST ID IS: " << artist_id << endl;
    callAPI_GENRE(artist_id);
}

//call api with inputed track name.
void callAPI_trackname_af(string trackname, string artistname) {
    string URI = "https://api.spotify.com/v1/search?q=";
    URI += parse_shit(trackname);
    URI += "+" + parse_shit(artistname);
    URI += "&type=track&limit=1";
    cout<<URI;

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
    cout << "the track id is: " << track_id;
    callAPI_audiofeatures(track_id, artistname);
    callAPI_artist_name(artistname);

}

//defining match arrays of your current profile with other profiles.
vector<double> genre_match(row_id);
vector<double> acoustic_match(row_id);
vector<double> danceability_match(row_id);
vector<double>energy_match(row_id);
vector<double> key_match(row_id);
vector <float> speechiness_match(row_id);
vector<int> mode_match(row_id);
vector<double>tempo_match(row_id);
vector<double>valence_match(row_id);
vector<double>liveness_match(row_id);

void _acoustic_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Acoustic FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> array(row_id);

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }

    for (int i = 0; i < row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[row_id - 1];
        cout << "\nacousticness of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        cout << "\n" << "acousticness of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) acoustic_match[i] = (1 - (parameter_1 - parameter_2)) * 6;
        else acoustic_match[i] = (1 - (parameter_2 - parameter_1)) * 6;
        cout << "the match percentage of acousticness of your profile with " << i << " profile is:" << acoustic_match[i] << endl;
    }
}

void _dancebility_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Danceability FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> array(row_id);

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }

    for (int i = 0; i < row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[row_id - 1];
        cout << "\ndanceability of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        cout << "\n" << "danceability of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) danceability_match[i] = (1 - (parameter_1 - parameter_2)) * 8;
        else danceability_match[i] = (1 - (parameter_2 - parameter_1)) * 8;
        cout << "the match percentage of danceability of your profile with " << i << " profile is:" << danceability_match[i] << endl;
    }
}

void _energy_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Energy FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> array(row_id);

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //energy of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }

    for (int i = 0; i < row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[row_id - 1];
        cout << "\nenergy of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        cout << "\n" << "energy of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) energy_match[i] = (1 - (parameter_1 - parameter_2)) * 6;
        else energy_match[i] = (1 - (parameter_2 - parameter_1)) * 6;
        cout << "the match percentage of energy of your profile with " << i << " profile is:" << energy_match[i] << endl;
    }
}

void _key_comparison() {
    //selecting key column from table.
    string query_3 = "SELECT Key FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <int> array(row_id);

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stoi(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }

    for (int i = 0; i < row_id - 1; i++) {
        //storing the last/latest/the current user profile.
        int parameter_1 = array[row_id - 1];
        cout << "\nkey of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        int parameter_2 = array[i];
        cout << "\n" << "key of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        double a;
        if (parameter_1 > parameter_2)
        {
            a = parameter_1 - parameter_2;
            key_match[i] = ((11 - a) / 11) * 6;
        }
        else {
            a = parameter_2 - parameter_1;
            key_match[i] = ((11 - a) / 11) * 6;
        }
        cout << "the key match of your profile with " << i << " profile is: " << key_match[i];
    }
}

void _speechiness_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Speechiness FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <float> array(row_id);

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stof(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }

    for (int i = 0; i < row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        float parameter_1 = array[row_id - 1];
        cout << "\nacousticness of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        float parameter_2 = array[i];
        cout << "\n" << "speechiness of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) speechiness_match[i] = (1 - (parameter_1 - parameter_2)) * 6;
        else speechiness_match[i] = (1 - (parameter_2 - parameter_1)) * 6;
        cout << "the match percentage of speechiness of your profile with " << i << " profile is:" << speechiness_match[i] << endl;
    }
}

void _mode_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Mode FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <int> array(row_id);

    //looping every parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stoi(_genres);
    }

    //mode of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }

    for (int i = 0; i < row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        int parameter_1 = array[row_id - 1];
        cout << "\nacousticness of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        int parameter_2 = array[i];
        cout << "\n" << "speechiness of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 == parameter_2) mode_match[i] = 6;
        else mode_match[i] = 3;
        cout << "the match percentage of mode of your profile with " << i << " profile is:" << mode_match[i] << endl;
    }
}

void _tempo_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Tempo FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> array(row_id);

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }

    for (int i = 0; i < row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[row_id - 1];
        cout << "\ntempo of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        cout << "\n" << "tempo of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) tempo_match[i] = (((200 - (parameter_1 - parameter_2)) / 200) * 6);
        else tempo_match[i] = (((200 - (parameter_2 - parameter_1)) / 200) * 6);
        cout << "the match percentage of tempo of your profile with " << i << " profile is:" << tempo_match[i] << endl;
    }
}

void _valence_comparison() {
    //selecting valence column from table.
    string query_3 = "SELECT Valence FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> array(row_id);

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }

    for (int i = 0; i < row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[row_id - 1];
        cout << "\nacousticness of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        cout << "\n" << "valence of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) valence_match[i] = (1 - (parameter_1 - parameter_2)) * 10;
        else valence_match[i] = (1 - (parameter_2 - parameter_1)) * 10;
        cout << "the match percentage of valence of your profile with " << i << " profile is:" << valence_match[i] << endl;
    }

}

void _liveness_comparison() {
    string query_3 = "SELECT Liveness FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> array(row_id);

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //liveness of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }

    for (int i = 0; i < row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[row_id - 1];
        cout << "\nliveness of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        cout << "\n" << "liveness of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) liveness_match[i] = (((60 - (parameter_1 - parameter_2)) / 60) * 6);
        else liveness_match[i] = (((60 - (parameter_2 - parameter_1)) / 60) * 6);
        cout << "the match percentage of liveness of your profile with " << i << " profile is:" << liveness_match[i] << endl;
    }
}

//ffs literally took nearly 5 hours to write this ass algorithm. man it was hell of an emotional ride.
void _genre_comparison() {
    //selecting genres column from table.
    string query_3 = "SELECT Genres FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;

    //creating an array to store each genres from each profile as a different element in array whose size is last row id.
    vector<string> array(row_id);

    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = _genres;
    }
    //genres of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < row_id; i++) {
        cout << i << " " << array[i] << endl;
    }
    //match percentage shit.
    //looping through each elements of array.
    for (int i = 0; i < row_id-1; i++) {

        //storing the last/latest/the current user profile.
        string genre_1 = array[row_id-1];
        cout << "\ngenre of latest inserted profile:\n" << genre_1 << endl;

        //looping through every element of array.
        string genre_2 = array[i];
        cout << "\n" << "genre of " << i << "profile:\n" << genre_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        //a is a temp string.
        string a;
        //creating an array_1 that stores separate genre distinguished by newline.
        string genre_array_1[20] = {};
        //ffs count_1/count_2 important affffff.
        //count_1/count_2 increases by 1 if any new line or last element is met and later on determines the size of array with genres filled. 
        int count_1 = 0;
        for (int i = 0; i <= genre_1.size(); i++) {
            //if a character is new line or last element of string, then count is added by 1 and until new line string is added in array.
            if (genre_1[i] == '\n' || genre_1[i] == genre_1[genre_1.size()]) {
                count_1++;
                genre_array_1[count_1 - 1] = a;
                a.erase(0, a.size());
            }
            else a += genre_1[i];
        }
        cout << count_1 << " datas were stored in genre 1 array:" << endl;
        for (int i = 0; i < count_1; i++) {
            cout << i << " " << genre_array_1[i] << endl;
        }

        //creating an array of second profile genres.
        //new line counts. 
        //same shit as first array.
        int count_2 = 0;
        string genre_array_2[20] = {};
        for (int i = 0; i <= genre_2.size(); i++) {
            if (genre_2[i] == '\n' || genre_2[i] == genre_2[genre_2.size()]) {
                count_2++;
                genre_array_2[count_2 - 1] = a;
                a.erase(0, a.size());
            }
            else a += genre_2[i];

        }
        cout << "\n" << count_2 << " datas were stored in genre 2 array:" << endl;
        for (int i = 0; i < count_2; i++) {
            cout << i << " " << genre_array_2[i] << endl;
        }
        double match=0;
        cout << "currently match is:"<<match<<endl;
        
        //bubble sort kind of... and here's he again the count_1 mf. this is vital afff boiiii.
        for (int i = 0; i < count_1; i++) {
            for (int j = 0; j < count_2; j++) {
                string genre1 = genre_array_1[i];
                string genre2 = genre_array_2[j];


                if (genre1 == genre2) {
                    
                    match += 10;
                }
                //exits the loop if the whole string matches.
                // eg : "indie folk" == "indie folk"
                else {
                    vector<string> token1;
                    vector<string> token2;
                    tokenize(genre1, ' ', token1);
                    tokenize(genre2, ' ', token2);


                    //compares a word
                    for (int i = 0; i < token1.size(); i++) {
                        for (int j = 0; j < token2.size(); j++) {
                            if (token1[i] == token2[j]) {
                                match += 5;
                                break;
                            }
                        }
                    }
                }
            }
        }
        

        genre_match[i] = (match/100) * 40;
        if (genre_match[i] >= 40) genre_match[i] = 40;
        cout << "the matched percentage is:" << genre_match[i] << endl;
    }
    

}


int main(int argc, char** argv) {

    cout << "Testing..." << endl;
    //checking the connection line in worldlink.
    connection();
    //checking all usernames stored in databass.
    
    userProfile_check();
    /*
username_check:
    cout << "enter your username:" << endl;
    string username="loduuu";
    //getline(cin, username);
    for (int i = 0; i < row_id; i++) {
        if (username == Profile_names[i]) {
            cout << "it seems your username already exists, try using another username." << endl;
            goto username_check;
        }
    }
    
    /*int check = 0;
    for (int i = 0; i < row_id; i++) {
        if (username == Profile_names[i]) {
            cout << "it seems your username already exists." << endl;
            cout <<"if you want to overwrite data under the same username..." << "\n"
                << "type \"2\" if you want to use another username... " << endl;
            string response;
            getline(cin, response);
            if (response == "1") {
                check++;
                break;
            }
            else {
                goto username_check;
            }
        }
    }
    */
    /*
    string trackName;
    string artistName;
    
    cout << "\n" << "\"FIRST QUESTION\"" << endl;
    cout << "NAME A SONG YOU'VE OVERPLAYED LIKE 1000 TIMES:" << endl;
    cout << "the song name:" << endl;
    getline(cin, trackName);
    cout << "the song's artist name:" << endl;
    getline(cin, artistName);
    callAPI_trackname_af(trackName, artistName);
    */
    /*
    cout << "\n" << "\"SECOND QUESTION\"" << endl;
    cout << "NAME A SONG THAT DEFINES YOU AS A PERSON:" << endl;
    cout << "the song name:" << endl;
    getline(cin, trackName);
    cout << "the song's artist name:" << endl;
    getline(cin, artistName);
    callAPI_artist_name(artistName);
    
    cout << "\n" << "\"THIRD QUESTION\"" << endl;
    cout << "NAME YOUR FAVOURITE ARTIST:" << endl;
    cout << "the artist name:" << endl;
    getline(cin, artistName);
    callAPI_artist_name(artistName);

    cout << "NAME YOUR FAVOURITE ARTIST:" << endl;
    cout << "the artist name:" << endl;
    getline(cin, artistName);
    callAPI_artist_name(artistName);

    cout << "NAME YOUR FAVOURITE ARTIST:" << endl;
    cout << "the artist name:" << endl;
    getline(cin, artistName);
    callAPI_artist_name(artistName);
    
    row_id++;
    adding_up(row_id , username, feature_af[0], feature_af[1], feature_af[2], int(feature_af[3]), feature_af[4], int(feature_af[5]), feature_af[6], feature_af[7], feature_af[8], _Genres);
    
    /*
    if (check == 1) update_shit(username, feature_af[0], feature_af[1], feature_af[2], int(feature_af[3]), feature_af[4], int(feature_af[5]), feature_af[6], feature_af[7], feature_af[8], _Genres);
    else adding_up(username, feature_af[0], feature_af[1], feature_af[2], int(feature_af[3]), feature_af[4], int(feature_af[5]), feature_af[6], feature_af[7], feature_af[8], _Genres);
    */
    //comparing every stored datas from database.
    cout << "\nCOMPARING RETRIEVED DATAS FROM YOU TO ALL OTHER AVAILABLE PROFILES..." << endl;
    _genre_comparison();
    _acoustic_comparison();
    _dancebility_comparison();
    _energy_comparison();
    _key_comparison();
    _speechiness_comparison();
    _mode_comparison();
    _tempo_comparison();
    _valence_comparison();
    _liveness_comparison();
    //delete_shit();
    
    //adding all compared stats from each profile available.
    vector<double> TOTAL_MATCHUP(row_id);
    for (int i = 0; i < row_id-1; i++) {
        TOTAL_MATCHUP[i] = genre_match[i] + acoustic_match[i] + danceability_match[i] + energy_match[i] + key_match[i] + speechiness_match[i] + mode_match[i]
            + tempo_match[i] + valence_match[i] + liveness_match[i];
    }

    //bubble sorting out shit in descending order.
    for (int i = 0; i < row_id; i++) {
        for (int j = i+1; j < row_id; j++) {
            if (TOTAL_MATCHUP[i] < TOTAL_MATCHUP[j]) {
                double _temp;
                string __temp;
                _temp = TOTAL_MATCHUP[i];
                TOTAL_MATCHUP[i] = TOTAL_MATCHUP[j];
                TOTAL_MATCHUP[j] = _temp;
                __temp = Profile_names[i];
                Profile_names[i] = Profile_names[j];
                Profile_names[j] = __temp;
            }
        }
    }

    string name;
    cout << "\n \nBROSKI, THESE ARE THE PROFILES YOUR MUSIC TASTE MATCHED THE MOST...\n" << endl;
    for (int i = 0; i < 5; i++) {
        cout << Profile_names[i] << " with  " << TOTAL_MATCHUP[i] << " %." << endl;
    }
    
    //closing the database.
    sqlite3_close(db);

    return 0;
}
