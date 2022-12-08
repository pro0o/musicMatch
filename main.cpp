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
vector <string> Profile_names;
vector <string> artistNAME;
sqlite3* db;
sqlite3_stmt* stmt;


//defining match arrays of your current profile with other profiles.
vector<double> genre_match;
vector<double> acoustic_match;
vector<double> danceability_match;
vector<double>energy_match;
vector<double> key_match;
vector <float> speechiness_match;
vector<int> mode_match;
vector<double>tempo_match;
vector<double>valence_match;
vector<double>liveness_match;


//functions def
void callAPI_artist_name(string artistName);

//token from spotify.
const string TOKEN = "";

//global variables.
double feature_af[9] = {};

//connecting to database.
void connection() {
    if (sqlite3_open("music_match00.db", &db) == SQLITE_OK) {
        string query_1 = "CREATE TABLE IF NOT EXISTS music_match(artist_name VARCHAR(10), Profile_Name VARCHAR(10), Acoustic DOUBLE, Danceability DOUBLE, Energy DOUBLE, Key INT, Speechiness DOUBLE, Mode INT, Tempo DOUBLE, Valence DOUBLE, Liveness DOUBLE, Genres VARCHAR(100));";
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
        Profile_names.push_back(_genres);
    }
}

void artistname_check() {
    //selecting Profile_Name column from table.
    string query_3 = "SELECT artist_name FROM music_match";
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
        artistNAME.push_back(_genres);
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

void adding_up(string artist_name, string Profile_Name, double Acoustic, double Danceability, double Energy, int Key, double Speechiness, int Mode, double Tempo, double Valence, double Liveness, string genres) {
    string insertQuery = "INSERT INTO music_match(artist_name, Profile_Name, Acoustic, Danceability, Energy, Key, Speechiness, Mode, Tempo, Valence, Liveness, Genres) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
        sqlite3_stmt * insertStmt;
    sqlite3_prepare(db, insertQuery.c_str(), insertQuery.size(), &insertStmt, NULL);
    sqlite3_bind_text(insertStmt, 1, artist_name.c_str(), artist_name.length(), SQLITE_TRANSIENT);
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
    else cout << "Your profile was successfully added."<<endl;
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
    //cout << '\n' << '\n' << "Again, calling an api request for AUDIO FEATURES using retreived unique track id." << endl;
    cout << "\nRetreiving Audio features..." << endl;
    switch (r.status_code) {
    case 200:
        cout << "THE AUDIO FEATURES WERE RETRIEVED." << endl;
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
        //cout << "the " << feature[i] << " of the song is : " << feature_af[i] << endl;
    }
}

void callAPI_GENRE(string artist_id) {

    string URI = "https://api.spotify.com/v1/artists/";
    URI = URI + artist_id;
    //cout << URI;
    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    //cout << '\n' << "NOW AGAIN, REQUESTING API FOR GENRES WITH THE RETRIEVED UNIQUE ARTIST ID." << '\n';
    cout << "\nRetreiving GENRES...." << endl;
    switch (r.status_code) {
    case 200:
        cout << "GENRES WERE RETREIVED." << endl;
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

        //cout << "\n" << count_1 << " datas were stored in genres array:" << endl;
        for (int i = 0; i < count_1; i++) {
            //cout << i << " " << genre_array_1[i] << endl;
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

        //std::cout << count_2 << " datas were stored in genre 1 array:" << endl;
        for (int i = 0; i < count_2; i++) {
            //cout << i << " " << genre_array_2[i] << endl;
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
            //cout << *it<<"+";
            _Genres += *it + "\n";
        }
        //remove end new line.
        _Genres.pop_back();
        //std::cout << "The element of set s are :" << std::endl;
        //std::cout << _Genres << std::endl;
        //std::cout << "genres stored in this session are:" << _Genres << std::endl;
    }
}

//call spotify api with trackname and artist name (3rd question)
void callAPI_artist_name(string artistName) {

    string URI = "https://api.spotify.com/v1/search?q=";
    URI = URI + parse_shit(artistName);
    URI = URI + "&type=artist&limit=1";
    //cout << URI;

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    cout << "\n" << "REQUESTING AN API REQUEST FOR AN UNIQUE ARTIST ID:" << endl;
    //cout << "calling an api request to retrieve artist id." << '\n';

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
    string artist_id = getartistid(r.text);
    //cout << "THE ARTIST ID IS: " << artist_id << endl;
    callAPI_GENRE(artist_id);
}

//call api with inputed track name.
void callAPI_trackname_af(string trackname, string artistname) {
    string URI = "https://api.spotify.com/v1/search?q=";
    URI += parse_shit(trackname);
    URI += "+" + parse_shit(artistname);
    URI += "&type=track&limit=1";

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    cout << "\n" << "REQUESTING AN API CALL FOR AN UNIQUE TRACK ID:" << endl;
    //cout << "calling an api request to retrieve track id." << endl;

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
    //cout << "the track id is: " << track_id;
    callAPI_audiofeatures(track_id, artistname);
    callAPI_artist_name(artistname);

}


void _acoustic_comparison() {
    cout << "acoustic row id is:" << row_id << endl;
    //selecting acoustic column from table.
    string query_3 = "SELECT Acoustic FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> acoustics_vector;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        acoustics_vector.push_back(stod(_genres));
    }
    /*
    //acousticnesss of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }*/


    //storing the last/latest/the current user profile.
    double curr_user_acoustics = acoustics_vector[row_id - 1];
    //cout << "\nacousticness of latest inserted profile: " << curr_user_acoustics << endl;

    for (int i = 0; i < row_id - 1; i++) {
        //looping through every element of array.
        double other_user_acoustic = acoustics_vector[i];
        //cout << "\n" << "acousticness of " << i << " profile: " << other_user_acoustic << endl;
        //cout << "\n" << "COMPARING SHIT..." << endl;

        double obtained_acoustics = (1 - abs(curr_user_acoustics - other_user_acoustic)) * 6;
        acoustic_match.push_back(obtained_acoustics);
        //cout << "the match percentage of acousticness of your profile with " << i << " profile is:" << acoustic_match[i] << endl;
    }
  
}

void _dancebility_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Danceability FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> dancebility_vector;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        dancebility_vector.push_back(stod(_genres));
    }
    //storing the last/latest/the current user profile.
    double curr_user_dancebility = dancebility_vector[row_id - 1];
    //cout << "\nacousticness of latest inserted profile: " << curr_user_dancebility << endl;

    for (int i = 0; i < row_id - 1; i++) {
        //looping through every element of array.
        double other_user_dancebility = dancebility_vector[i];
        //cout << "\n" << "dancebility of " << i << " profile: " << other_user_dancebility << endl;
        //cout << "\n" << "COMPARING SHIT..." << endl;

        double obtained_dancebility = (1 - abs(curr_user_dancebility - other_user_dancebility)) * 8;
        danceability_match.push_back(obtained_dancebility);
        //cout << "the match percentage of acousticness of your profile with " << i << " profile is:" << danceability_match[i] << endl;
    }
}

void _energy_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Energy FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> energy_vector;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        energy_vector.push_back(stod(_genres));
    }

    //storing the last / latest / the current user profile.
        double curr_user_energy = energy_vector[row_id - 1];
    //cout << "\nacousticness of latest inserted profile: " << curr_user_energy << endl;

    for (int i = 0; i < row_id - 1; i++) {
        //looping through every element of array.
        double other_user_energy = energy_vector[i];
        //cout << "\n" << "energy of " << i << " profile: " << other_user_energy << endl;
        //cout << "\n" << "COMPARING SHIT..." << endl;

        double obtained_energy = (1 - abs(curr_user_energy - other_user_energy)) * 6;
        energy_match.push_back(obtained_energy);
        //cout << "the match percentage of energy of your profile with " << i << " profile is:" << energy_match[i] << endl;
    }
}

void _key_comparison() {
    //selecting key column from table.
    string query_3 = "SELECT Key FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <int> key_vector;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        key_vector.push_back(stoi(_genres));
    }

    for (int i = 0; i < row_id - 1; i++) {
        //storing the last/latest/the current user profile.
        int parameter_1 = key_vector[row_id - 1];
        //cout << "\nkey of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        int parameter_2 = key_vector[i];
        //cout << "\n" << "key of " << i << " profile: " << parameter_2 << endl;
        //cout << "\n" << "COMPARING SHIT..." << endl;
        double a;
        if (parameter_1 > parameter_2)
        {
            a = parameter_1 - parameter_2;
            key_match.push_back (((11 - a) / 11) * 6);
        }
        else {
            a = parameter_2 - parameter_1;
            key_match.push_back(((11 - a) / 11) * 6);
        }
        //cout << "the key match of your profile with " << i << " profile is: " << key_match[i];
    }
}

void _speechiness_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Speechiness FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <float> speechiness_vector;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        speechiness_vector.push_back(stof(_genres));
    }
    //storing the last / latest / the current user profile.
        double curr_user_speechiness = speechiness_vector[row_id - 1];
    //cout << "\nspeechiness of latest inserted profile: " << curr_user_speechiness << endl;

    for (int i = 0; i < row_id - 1; i++) {
        //looping through every element of array.
        double other_user_speechiness = speechiness_vector[i];
        //cout << "\n" << "speechiness of " << i << " profile: " << other_user_speechiness << endl;
        //cout << "\n" << "COMPARING SHIT..." << endl;

        double obtained_speechiness = (1 - abs(curr_user_speechiness - other_user_speechiness)) * 6;
        speechiness_match.push_back(obtained_speechiness);
        //cout << "the match percentage of acousticness of your profile with " << i << " profile is:" <<speechiness_match[i] << endl;
    }
}

void _mode_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Mode FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <int> mode_vector;

    //looping every parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        mode_vector.push_back(stoi(_genres));
    }

    // storing the last / latest / the current user profile.
        double curr_user_mode = mode_vector[row_id - 1];
    //cout << "\nmode of latest inserted profile: " << curr_user_mode<< endl;

    for (int i = 0; i < row_id - 1; i++) {
        //looping through every element of array.
        double other_user_mode = mode_vector[i];
        //cout << "\n" << "mode of " << i << " profile: " << other_user_mode << endl;
        //cout << "\n" << "COMPARING SHIT..." << endl;
        double obtained_mode;
        if (curr_user_mode == other_user_mode) obtained_mode = 6;
        else obtained_mode = 1;
        mode_match.push_back(obtained_mode);
        //cout << "the match percentage of mode of your profile with " << i << " profile is:" << mode_match[i] << endl;
    }
}

void _tempo_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Tempo FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> tempo_vector;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        tempo_vector.push_back(stod(_genres));
    }
    // storing the last / latest / the current user profile.
        double curr_user_tempo = tempo_vector[row_id - 1];
    //cout << "\ntempo of latest inserted profile: " << curr_user_tempo << endl;

    for (int i = 0; i < row_id - 1; i++) {
        //looping through every element of array.
        double other_user_tempo = tempo_vector[i];
        //cout << "\n" << "tempo of " << i << " profile: " << other_user_tempo << endl;
        //cout << "\n" << "COMPARING SHIT..." << endl;

        double obtained_tempo = (((200 - (curr_user_tempo - other_user_tempo)) / 200) * 6);
        tempo_match.push_back(obtained_tempo);
        //cout << "the match percentage of acousticness of your profile with " << i << " profile is:" << tempo_match[i] << endl;
    }
}

void _valence_comparison() {
    //selecting valence column from table.
    string query_3 = "SELECT Valence FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> valence_vector;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        valence_vector.push_back(stod(_genres));
    }
    // storing the last / latest / the current user profile.
    double curr_user_valence = valence_vector[row_id - 1];
    //cout << "\nvalence of latest inserted profile: " << curr_user_valence << endl;

    for (int i = 0; i < row_id - 1; i++) {
        //looping through every element of array.
        double other_user_valence = valence_vector[i];
        //cout << "\n" << "valence of " << i << " profile: " << other_user_valence << endl;
        //cout << "\n" << "COMPARING SHIT..." << endl;

        double obtained_valence = (1 - abs(curr_user_valence - other_user_valence)) * 10;
        valence_match.push_back(obtained_valence);
        //cout << "the match percentage of valence of your profile with " << i << " profile is:" << valence_match[i] << endl;

    }

}

void _liveness_comparison() {
    //cout << "the row id is :" << row_id;
    string query_3 = "SELECT Liveness FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    vector <double> liveness_vector;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        liveness_vector.push_back(stod(_genres));
    }
    // storing the last / latest / the current user profile.
    double curr_user_liveness = liveness_vector[row_id - 1];
    //cout << "\nliveness of latest inserted profile: " << curr_user_liveness << endl;

    for (int i = 0; i < row_id-1; i++) {
        //looping through every element of array.
        double other_user_liveness = liveness_vector[i];
        //cout << "\n" << "liveness of " << i << " profile: " << other_user_liveness << endl;
        double obtained_liveness = (((60 - abs(curr_user_liveness - other_user_liveness)) / 60) * 6);
        liveness_match.push_back(obtained_liveness);
        //cout << "the match percentage of liveness of your profile with " << i << " profile is:" << liveness_match[i] << endl;
    }
}

/*
//ffs literally took nearly 5 hours to write this ass algorithm. man it was hell of an emotional ride.
void _genre_comparison() {
    row_id--;
    cout << "row_id : " << row_id << endl;

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

    //match percentage shit.
    //looping through each elements of array.

    //storing the last/latest/the current user profile.
    string genre_1 = array[row_id - 1];

    for (int i = 0; i < row_id-1; i++) {

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
        for (int i = 0; i < genre_1.size(); i++) {
            //if a character is new line or last element of string, then count is added by 1 and until new line string is added in array.
            if (genre_1[i] == '\n' || i == genre_1.size() -1) {
                count_1++;
                genre_array_1[count_1 - 1] = a;
                a = "";
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
        for (int i = 0; i < genre_2.size(); i++) {
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
        

        genre_match[i] = (match / 100) * 40;
        if (genre_match[i] >= 40) genre_match[i] = 40;
        cout << "the matched percentage is:" << genre_match[i] << endl;
  
    }
    

}*/

void _genre_comparison() {
    //selecting genres column from table.
    string query_3 = "SELECT Genres FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;

    //creating an array to store each genres from each profile as a different element in array whose size is last row id.
    vector<string> genre_string(row_id);

    for (int i = 0; i < row_id; i++){
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        genre_string[i] = _genres;
    }

    string genre_of_curr_user = genre_string[row_id - 1];
    string _temp;
    vector<string> curr_user_genre;
    for (int i = 0; i < genre_of_curr_user.size(); i++) {
        if (genre_of_curr_user[i] == '\n' || i == genre_of_curr_user.size() - 1) {
            curr_user_genre.push_back(_temp);
            _temp = "";
        }
        else _temp += genre_of_curr_user[i];
    }


    //cout << "current genres obtained success fully\n";
        //for (auto e : curr_user_genre)cout << e << endl;

    for (int i = 0; i < row_id - 1; i++) {
        string genre_of_user = genre_string[i];
        vector<string> genre;
        for (int i = 0; i < genre_of_user.size(); i++) {
            if (genre_of_user[i] == '\n' || i == genre_of_user.size() - 1) {
                if (i == genre_of_user.size() - 1)_temp += genre_of_user[i];
                genre.push_back(_temp);
                _temp = "";
            }
            else _temp += genre_of_user[i];
        }
        /*
        cout << "other users genres obtained success fully\n";
        cout << "FOR USER : " << i + 1 << endl;
        for (auto e : genre)cout << e << endl;
        */

        double match = 0;
        for (int i = 0; i < curr_user_genre.size(); i++) {
            if (i >= genre.size())break;
            for (int j = 0; j < genre.size(); j++) {
                string genre_curr = curr_user_genre[i];
                string genre_user = genre[j];

                if (genre_curr == genre_user) match += 7;
                else {
                    vector<string> token1;
                    vector<string> token2;
                    tokenize(genre_curr, ' ', token1);
                    tokenize(genre_user, ' ', token2);


                    //compares a word
                    for (int i = 0; i < token1.size(); i++) {
                        for (int j = 0; j < token2.size(); j++) {
                            if (token1[i] == token2[j]) {
                                match += 3;
                                break;
                            }
                        }
                    }
                }
            }
        }
        match  = (match / 100) * 40;
        if (match >= 40) match = 40;
        genre_match.push_back(match);
    }
}

static int callback(void* count, int argc, char** argv, char** azColName) {
    int* c = (int *)count;
    *c = atoi(argv[0]);
    return 0;
}


int main(int argc, char** argv) {

    cout << "Testing..." << endl;
    //checking the connection line in worldlink.
    connection();
    //find the last row_id.
    char* zErrMsg;
    int rc = sqlite3_exec(db, "select count(*) from music_match", callback, &row_id, &zErrMsg);
    std::cout << "row_id : " << row_id << endl;
    if (rc != SQLITE_OK)std::cerr << "SQL error" << std::endl;
    
    //checking all usernames stored in databass.
    userProfile_check();
    string username;
    username_check:

    cout << "enter your username:" << endl;
    getline(cin, username);
    
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

    string trackName;
    string artistName;
    
    cout << "\n" << "\"FIRST QUESTION\"" << endl;
    cout << "NAME YOUR MOST PLAYED SONG:" << endl;
    cout << "the song name:" << endl;
    getline(cin, trackName);
    cout << "the song's artist name:" << endl;
    getline(cin, artistName);
    callAPI_trackname_af(trackName, artistName);

    cout << "\n" << "\"SECOND QUESTION\"" << endl;
    cout << "NAME YOUR RECENT FAVOURITE SONG:" << endl;
    cout << "the song name:" << endl;
    getline(cin, trackName);
    cout << "the song's artist name:" << endl;
    getline(cin, artistName);
    callAPI_artist_name(artistName);
    
    string artistName_1;
    cout << "\n" << "\"THIRD QUESTION\"" << endl;
    cout << "ENTER YOUR THREE FAVOURITE ARTISTS:" << endl;
    cout << "I, "<<endl;
    cout << "the artist name:" << endl;
    getline(cin, artistName_1);
    callAPI_artist_name(artistName_1);

    cout << "II, " << endl;
    cout << "the artist name:" << endl;
    getline(cin, artistName);
    callAPI_artist_name(artistName);

    cout << "III, "<<endl;
    cout << "the artist name:" << endl;
    getline(cin, artistName);
    callAPI_artist_name(artistName);

    //commmet


    adding_up( artistName_1, username, feature_af[0], feature_af[1], feature_af[2], int(feature_af[3]), feature_af[4], int(feature_af[5]), feature_af[6], feature_af[7], feature_af[8], _Genres);
    /*
    if (check == 1) update_shit(username, feature_af[0], feature_af[1], feature_af[2], int(feature_af[3]), feature_af[4], int(feature_af[5]), feature_af[6], feature_af[7], feature_af[8], _Genres);
    else adding_up(username, feature_af[0], feature_af[1], feature_af[2], int(feature_af[3]), feature_af[4], int(feature_af[5]), feature_af[6], feature_af[7], feature_af[8], _Genres);
    */
    //comparing every stored datas from database
    
    cout << "\nCOMPARING RETRIEVED DATAS FROM YOU TO ALL OTHER AVAILABLE PROFILES..............." << endl;
    //altering the value of row id with recent insert id.
    row_id = sqlite3_last_insert_rowid(db);
    
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

    //artistname_check();

    //bubble sorting out shit in descending order.
    for (int i = 0; i < row_id; i++) {
        for (int j = i+1; j < row_id; j++) {
            if (TOTAL_MATCHUP[i] < TOTAL_MATCHUP[j]) {
                double _temp;
                string __temp;
                //string ___temp;
                _temp = TOTAL_MATCHUP[i];
                TOTAL_MATCHUP[i] = TOTAL_MATCHUP[j];
                TOTAL_MATCHUP[j] = _temp;
                __temp = Profile_names[i];
                Profile_names[i] = Profile_names[j];
                Profile_names[j] = __temp;
                //___temp = artistNAME[i];
                //artistNAME[i] = artistNAME[j];
                //artistNAME[j] = ___temp;
            }
        }
    }

    string name;
    cout << "\nBROSKI, THESE ARE THE PROFILES YOUR MUSIC TASTE MATCHED THE MOST:\n" << endl;
    for (int i = 0; i < 5; i++) {
        cout << Profile_names[i] << " with  " << TOTAL_MATCHUP[i] << " %." << endl;
    }
    //cout << "\nand one of " << Profile_names[0] << "'s favourite artist was "<<artistName[0]<< endl;
    //closing the database.
    sqlite3_close(db);


    return 0;
}
