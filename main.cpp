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
string Profile_Name = "bozo";
int _count = 0;

//manual input of last row id.
const int last_row_id = 2;

//defining match arrays of your current profile with other profiles.
int genre_match[last_row_id] = {};
double acoustic_match[last_row_id] = {};
double danceability_match[last_row_id] = {};
double energy_match[last_row_id] = {};
int key_match[last_row_id] = {};
float speechiness_match[last_row_id] = {};
int mode_match[last_row_id] = {};
double tempo_match[last_row_id] = {};
double valence_match[last_row_id] = {};
double liveness_match[last_row_id] = {};

//token from spotify.
const string TOKEN = "BQB7wThMiH_YRLsPGceKF17fAVvofghjYGIfV5RAodFKCW0QdKHtzucj1_LuwtBY_XekFDnYV7kJolbZY6zwnZu9hOMSzF2ypvZWnsJdKnBunwRaDQJ7Ko1TPHqbFFdkm9hvKoImtHTzDxQ30JY9qwthQpCejewwoHLKZ30EczmLCptN-UWHaQVgrAhloMOlFIly7WUbNPjWVAq1fHBfISQKEmU-IX353BSUa2EM7PrSEW7XUnhxutZtwJ6JB8AX9hy2rruyYA";

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
        _count++;

    }
}

void read_data() {
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
    _count--;
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

void _acoustic_comparison() {
    //selecting acoustic column from table.
    string query_3 = "SELECT Acoustic FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};
    
    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
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

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
        cout << "\nacousticness of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        cout << "\n" << "acousticness of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if(parameter_1>parameter_2) acoustic_match[i] = (1 - (parameter_1 - parameter_2)) * 6;
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
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
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

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
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
    //selecting energy column from table.
    string query_3 = "SELECT Energy FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
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

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
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
    int array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
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

    for (int i = 0; i < last_row_id - 1; i++) {
        //storing the last/latest/the current user profile.
        int parameter_1 = array[last_row_id - 1];
        cout << "\nkey of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        int parameter_2 = array[i];
        cout << "\n" << "key of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) key_match[i] = (((11 - (parameter_1 - parameter_2)) / 11)*6);
        else key_match[i] = (((11 - (parameter_2 - parameter_1)) / 11) * 6);
        cout << "the key match of your profile with " << i << " profile is: " << key_match[i];
    }
}

void _speechiness_comparison(){
//selecting acoustic column from table.
string query_3 = "SELECT Speechiness FROM music_match";
int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
//check the response.
if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
//creating an array to store each parameter from each profile as a different element in array whose size is last row id.
float array[last_row_id] = {};

//looping every acoustic parameter and storing as a unique element i
for (int i = 0; i < last_row_id; i++) {
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

for (int i = 0; i < last_row_id - 1; i++) {

    //storing the last/latest/the current user profile.
    float parameter_1 = array[last_row_id - 1];
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
    int array[last_row_id] = {};

    //looping every parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
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

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        int parameter_1 = array[last_row_id - 1];
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
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
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

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
        cout << "\ntempo of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        cout << "\n" << "tempo of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) tempo_match[i] = (((200 - (parameter_1 - parameter_2))/200) * 6);
        else tempo_match[i] = (((200 - (parameter_2 - parameter_1)) / 200) * 6);
        cout << "the match percentage of acousticness of your profile with " << i << " profile is:" << tempo_match[i] << endl;
    }
}

void _valence_comparison() {
    //selecting valence column from table.
    string query_3 = "SELECT Valence FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
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

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
        cout << "\nacousticness of latest inserted profile: " << parameter_1 << endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        cout << "\n" << "valence of " << i << " profile: " << parameter_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        if (parameter_1 > parameter_2) valence_match[i] = (1 - (parameter_1 - parameter_2)) * 10;
        else valence_match[i] = (1 - (parameter_2 - parameter_1)) * 10;
        cout << "the match percentage of acousticness of your profile with " << i << " profile is:" << valence_match[i] << endl;
    }
    
}

void _liveness_comparison() {
    string query_3 = "SELECT Liveness FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) cout << "ERROR: " << sqlite3_errmsg(db) << endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
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

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
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
    string array[last_row_id];

    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        string _genres = reinterpret_cast<const char*>(genres);
        array[i] = _genres;
    }
    //genres of each profile saved as an element in the array.
    cout << "datas stored in arrays:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n" << i << " " << array[i] << endl;
    }
    //match percentage shit.
    //looping through each elements of array.
    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        string genre_1 = array[last_row_id - 1];
        cout << "\ngenre of latest inserted profile:\n" << genre_1 << endl;

        //looping through every element of array.
        string genre_2 = array[i];
        cout << "\n" << "genre of " << i << "profile:\n" << genre_2 << endl;
        cout << "\n" << "COMPARING SHIT..." << endl;
        //a is a temp string.
        string a;
        //creating an array_1 that stores separate genre distinguished by newline.
        string genre_array_1[10] = {};
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
        string genre_array_2[10] = {};
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
        //bubble sort kind of... and here's he again the count_1 mf. this is vital afff boiiii.
        for (int i = 0; i < count_1; i++) {
            for (int j = 0; j < count_2; j++) {
                string genre1 = genre_array_1[i];
                string genre2 = genre_array_2[j];


                if (genre1 == genre2) {
                    genre_match[i] += 10;
                    cout << genre_match[i];
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
                                genre_match[i] += 5;
                                cout << genre_match[i];
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout << "the matched percentage is:" << genre_match[i] << endl;
    }

}

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

    //first creating a base for user table.
    connection();
    //comparing every stored datas from database.
    //_genre_comparison();
    //_acoustic_comparison();
    //_dancebility_comparison();
    //_energy_comparison();
    //_key_comparison();
    //_speechiness_comparison();
    //_mode_comparison();
    //_tempo_comparison();
    //_valence_comparison();
    //_liveness_comparison();
    //delete_shit();
    //update_shit();

    //adding all compared stats from each profile available.
    double TOTAL_MATCHUP[last_row_id] = {};
    for (int i = 0; i < last_row_id-1; i++) {
        TOTAL_MATCHUP[i] = genre_match[i] + acoustic_match[i] + danceability_match[i] + energy_match[i] + key_match[i] + speechiness_match[i] + mode_match[i]
            + tempo_match[i] + valence_match[i] + liveness_match[i];
        cout << "The match percent of your music taste with profile " << i << " is: " << TOTAL_MATCHUP[i] << endl;;
    }

    //bubble sorting out shit in descending order.
    for (int i = 0; i < last_row_id; i++) {
        for (int j = i+1; j < last_row_id; j++) {
            if (TOTAL_MATCHUP[i] < TOTAL_MATCHUP[j]) {
                double _temp;
                _temp = TOTAL_MATCHUP[i];
                TOTAL_MATCHUP[i] = TOTAL_MATCHUP[j];
                TOTAL_MATCHUP[j] = _temp;
            }
        }
    }

    string name;
    cout << "BROSKIIII, THESE ARE THE PROFILES YOUR MUSIC TASTE MATCHED THE MOST...\n" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Profile: " << name << " with match percent" << TOTAL_MATCHUP[i]<<endl;
    }

    sqlite3_close(db);

    return 0;
}
