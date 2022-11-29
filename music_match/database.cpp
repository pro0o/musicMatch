/*
#include "database.h"

sqlite3* db;
sqlite3_stmt* stmt;
const int last_row_id = 2;
std::string Profile_names[last_row_id] = {};

//adding all compared stats from each profile available.
double TOTAL_MATCHUP[last_row_id] = {};


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

//connecting to database.
void connection() {
    if (sqlite3_open("demo.db", &db) == SQLITE_OK) {

        std::string query_1 = "CREATE TABLE IF NOT EXISTS music_match(Profile_Name VARCHAR(10), Acoustic DOUBLE, Danceability DOUBLE, Energy DOUBLE, Key INT, Speechiness DOUBLE, Mode INT, Tempo DOUBLE, Valence DOUBLE, Liveness DOUBLE, Genres VARCHAR(100));";
        int response = sqlite3_prepare_v2(db, query_1.c_str(), -1, &stmt, NULL);
        //declare the statement.
        sqlite3_step(stmt);
        //delete the statement.
        sqlite3_finalize(stmt);
        if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
        else std::cout << "TABLE WAS CREATED SUCCESSFULLY." << std::endl;

    }
}

/*
//adding audio features and genres into a row(PROFILE).
void adding_up(std::string Profile_Name, double Acoustic, double Danceability, double Energy, int Key, double Speechiness, int Mode, double Tempo, double Valence, double Liveness, std::string genres) {
    if (sqlite3_open("demo.db", &db) == SQLITE_OK) {
        std::string query_2 = "INSERT INTO music_match(Profile_Name, Acoustic, Danceability, Energy, Key, Speechiness, Mode, Tempo, Valence, Liveness, Genres) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
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
        if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
        else std::cout << "NEW PROFILE WAS ADDED SUCCESSFULLY." << std::endl;
    }
}

void userProfile_check() {
    //selecting Profile_Name column from table.
    std::string query_3 = "SELECT Profile_Name FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response == sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        Profile_names[i] = _genres;
    }
}

void _acoustic_comparison() {
    //selecting acoustic column from table.
    std::string query_3 = "SELECT Acoustic FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "\n" << i << " " << array[i] << std::endl;
    }

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
        std::cout << "\nacousticness of latest inserted profile: " << parameter_1 << std::endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        std::cout << "\n" << "acousticness of " << i << " profile: " << parameter_2 << std::endl;
        std::cout << "\n" << "COMPARING SHIT..." << std::endl;
        if (parameter_1 > parameter_2) acoustic_match[i] = (1 - (parameter_1 - parameter_2)) * 6;
        else acoustic_match[i] = (1 - (parameter_2 - parameter_1)) * 6;
        std::cout << "the match percentage of acousticness of your profile with " << i << " profile is:" << acoustic_match[i] << std::endl;
    }
}

void _dancebility_comparison() {
    //selecting acoustic column from table.
    std::string query_3 = "SELECT Danceability FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "\n" << i << " " << array[i] << std::endl;
    }

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
        std::cout << "\ndanceability of latest inserted profile: " << parameter_1 << std::endl;

        //looping through every element of array.
        double parameter_2 = array[i];
       std:: cout << "\n" << "danceability of " << i << " profile: " << parameter_2 << std::endl;
        std::cout << "\n" << "COMPARING SHIT..." << std::endl;
        if (parameter_1 > parameter_2) danceability_match[i] = (1 - (parameter_1 - parameter_2)) * 8;
        else danceability_match[i] = (1 - (parameter_2 - parameter_1)) * 8;
        std::cout << "the match percentage of danceability of your profile with " << i << " profile is:" << danceability_match[i] << std::endl;
    }
}

void _energy_comparison() {
    //selecting acoustic column from table.
    std::string query_3 = "SELECT Energy FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //energy of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "\n" << i << " " << array[i] << std::endl;
    }

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
        std::cout << "\nenergy of latest inserted profile: " << parameter_1 << std::endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        std::cout << "\n" << "energy of " << i << " profile: " << parameter_2 << std::endl;
        std::cout << "\n" << "COMPARING SHIT..." << std::endl;
        if (parameter_1 > parameter_2) energy_match[i] = (1 - (parameter_1 - parameter_2)) * 6;
        else energy_match[i] = (1 - (parameter_2 - parameter_1)) * 6;
        std::cout << "the match percentage of energy of your profile with " << i << " profile is:" << energy_match[i] << std::endl;
    }
}

void _key_comparison() {
    //selecting key column from table.
    std::string query_3 = "SELECT Key FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    int array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stoi(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
       std:: cout << "\n" << i << " " << array[i] << std::endl;
    }

    for (int i = 0; i < last_row_id - 1; i++) {
        //storing the last/latest/the current user profile.
        int parameter_1 = array[last_row_id - 1];
        std::cout << "\nkey of latest inserted profile: " << parameter_1 << std::endl;

        //looping through every element of array.
        int parameter_2 = array[i];
       std:: cout << "\n" << "key of " << i << " profile: " << parameter_2 <<std:: endl;
        std::cout << "\n" << "COMPARING SHIT..." << std::endl;
        if (parameter_1 > parameter_2) key_match[i] = (((11 - (parameter_1 - parameter_2)) / 11) * 6);
        else key_match[i] = (((11 - (parameter_2 - parameter_1)) / 11) * 6);
        std::cout << "the key match of your profile with " << i << " profile is: " << key_match[i];
    }
}

void _speechiness_comparison() {
    //selecting acoustic column from table.
    std::string query_3 = "SELECT Speechiness FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    float array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stof(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
       std:: cout << "\n" << i << " " << array[i] << std::endl;
    }

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        float parameter_1 = array[last_row_id - 1];
        std::cout << "\nacousticness of latest inserted profile: " << parameter_1 << std::endl;

        //looping through every element of array.
        float parameter_2 = array[i];
       std:: cout << "\n" << "speechiness of " << i << " profile: " << parameter_2 << std::endl;
        std::cout << "\n" << "COMPARING SHIT..." << std::endl;
        if (parameter_1 > parameter_2) speechiness_match[i] = (1 - (parameter_1 - parameter_2)) * 6;
        else speechiness_match[i] = (1 - (parameter_2 - parameter_1)) * 6;
        std::cout << "the match percentage of speechiness of your profile with " << i << " profile is:" << speechiness_match[i] << std::endl;
    }
}

void _mode_comparison() {
    //selecting acoustic column from table.
    std::string query_3 = "SELECT Mode FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK)std:: cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    int array[last_row_id] = {};

    //looping every parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stoi(_genres);
    }

    //mode of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "\n" << i << " " << array[i] << std::endl;
    }

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        int parameter_1 = array[last_row_id - 1];
        std::cout << "\nacousticness of latest inserted profile: " << parameter_1 << std::endl;

        //looping through every element of array.
        int parameter_2 = array[i];
        std::cout << "\n" << "speechiness of " << i << " profile: " << parameter_2 << std::endl;
        std::cout << "\n" << "COMPARING SHIT..." << std::endl;
        if (parameter_1 == parameter_2) mode_match[i] = 6;
        else mode_match[i] = 3;
        std::cout << "the match percentage of mode of your profile with " << i << " profile is:" << mode_match[i] << std::endl;
    }
}

void _tempo_comparison() {
    //selecting acoustic column from table.
    std::string query_3 = "SELECT Tempo FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "\n" << i << " " << array[i] << std::endl;
    }

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
        std::cout << "\ntempo of latest inserted profile: " << parameter_1 << std::endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        std::cout << "\n" << "tempo of " << i << " profile: " << parameter_2 << std::endl;
       std::cout << "\n" << "COMPARING SHIT..." << std::endl;
        if (parameter_1 > parameter_2) tempo_match[i] = (((200 - (parameter_1 - parameter_2)) / 200) * 6);
        else tempo_match[i] = (((200 - (parameter_2 - parameter_1)) / 200) * 6);
        std::cout << "the match percentage of acousticness of your profile with " << i << " profile is:" << tempo_match[i] << std::endl;
    }
}

void _valence_comparison() {
    //selecting valence column from table.
    std::string query_3 = "SELECT Valence FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //acousticnesss of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "\n" << i << " " << array[i] << std::endl;
    }

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
        std::cout << "\nacousticness of latest inserted profile: " << parameter_1 << std::endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        std::cout << "\n" << "valence of " << i << " profile: " << parameter_2 << std::endl;
        std::cout << "\n" << "COMPARING SHIT..." << std::endl;
        if (parameter_1 > parameter_2) valence_match[i] = (1 - (parameter_1 - parameter_2)) * 10;
        else valence_match[i] = (1 - (parameter_2 - parameter_1)) * 10;
       std:: cout << "the match percentage of acousticness of your profile with " << i << " profile is:" << valence_match[i] <<std:: endl;
    }

}

void _liveness_comparison() {
    std::string query_3 = "SELECT Liveness FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;
    //creating an array to store each parameter from each profile as a different element in array whose size is last row id.
    double array[last_row_id] = {};

    //looping every acoustic parameter and storing as a unique element i
    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = stod(_genres);
    }

    //liveness of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "\n" << i << " " << array[i] << std::endl;
    }

    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        double parameter_1 = array[last_row_id - 1];
        std::cout << "\nliveness of latest inserted profile: " << parameter_1 << std::endl;

        //looping through every element of array.
        double parameter_2 = array[i];
        std::cout << "\n" << "liveness of " << i << " profile: " << parameter_2 << std::endl;
       std:: cout << "\n" << "COMPARING SHIT..." <<std:: endl;
        if (parameter_1 > parameter_2) liveness_match[i] = (((60 - (parameter_1 - parameter_2)) / 60) * 6);
        else liveness_match[i] = (((60 - (parameter_2 - parameter_1)) / 60) * 6);
        std::cout << "the match percentage of liveness of your profile with " << i << " profile is:" << liveness_match[i] << std::endl;
    }
}

//ffs literally took nearly 5 hours to write this ass algorithm. man it was hell of an emotional ride.
void _genre_comparison() {
    //selecting genres column from table.
    std::string query_3 = "SELECT Genres FROM music_match";
    int response = sqlite3_prepare_v2(db, query_3.c_str(), -1, &stmt, NULL);
    //check the response.
    if (response != SQLITE_OK) std::cout << "ERROR: " << sqlite3_errmsg(db) << std::endl;

    //creating an array to store each genres from each profile as a different element in array whose size is last row id.
    std::string array[last_row_id];

    for (int i = 0; i < last_row_id; i++) {
        if (response = sqlite3_step(stmt) == SQLITE_ROW)
            std::string genres;
        //convert const unsigned char* into string by typecasting.
        const unsigned char* genres = sqlite3_column_text(stmt, 0);
        std::string _genres = reinterpret_cast<const char*>(genres);
        array[i] = _genres;
    }
    //genres of each profile saved as an element in the array.
    std::cout << "datas stored in arrays:" << std::endl;
    for (int i = 0; i < 2; i++) {
        std::cout << "\n" << i << " " << array[i] << std::endl;
    }
    //match percentage shit.
    //looping through each elements of array.
    for (int i = 0; i < last_row_id - 1; i++) {

        //storing the last/latest/the current user profile.
        std::string genre_1 = array[last_row_id - 1];
        std::cout << "\ngenre of latest inserted profile:\n" << genre_1 << std::endl;

        //looping through every element of array.
        std::string genre_2 = array[i];
        std::cout << "\n" << "genre of " << i << "profile:\n" << genre_2 << std:: endl;
        std::cout << "\n" << "COMPARING SHIT..." << std::endl;
        //a is a temp string.
        std::string a;
        //creating an array_1 that stores separate genre distinguished by newline.
        std::string genre_array_1[10] = {};
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
        std::cout << count_1 << " datas were stored in genre 1 array:" << std::endl;
        for (int i = 0; i < count_1; i++) {
            std::cout << i << " " << genre_array_1[i] << std::endl;
        }

        //creating an array of second profile genres.
        //new line counts.
        //same shit as first array.
        int count_2 = 0;
        std::string genre_array_2[10] = {};
        for (int i = 0; i <= genre_2.size(); i++) {
            if (genre_2[i] == '\n' || genre_2[i] == genre_2[genre_2.size()]) {
                count_2++;
                genre_array_2[count_2 - 1] = a;
                a.erase(0, a.size());
            }
            else a += genre_2[i];

        }
        std::cout << "\n" << count_2 << " datas were stored in genre 2 array:" << std::endl;
        for (int i = 0; i < count_2; i++) {
           std:: cout << i << " " << genre_array_2[i] << std::endl;
        }
        //bubble sort kind of... and here's he again the count_1 mf. this is vital afff boiiii.
        for (int i = 0; i < count_1; i++) {
            for (int j = 0; j < count_2; j++) {
                std::string genre1 = genre_array_1[i];
                std::string genre2 = genre_array_2[j];


                if (genre1 == genre2) {
                    genre_match[i] += 10;
                    std::cout << genre_match[i];
                }
                //exits the loop if the whole string matches.
                // eg : "indie folk" == "indie folk"
                else {
                    std::vector<std::string> token1;
                    std::vector<std::string> token2;
                    tokenize(genre1, ' ', token1);
                    tokenize(genre2, ' ', token2);


                    //compares a word
                    for (int i = 0; i < token1.size(); i++) {
                        for (int j = 0; j < token2.size(); j++) {
                            if (token1[i] == token2[j]) {
                                genre_match[i] += 5;
                                std::cout << genre_match[i];
                                break;
                            }
                        }
                    }
                }
            }
        }
        std::cout << "the matched percentage is:" << genre_match[i] << std::endl;
    }

}

void _total_match_up(){
    for(int i = 0; i < last_row_id-1; i++) {
        TOTAL_MATCHUP[i] = genre_match[i] + acoustic_match[i] + danceability_match[i] + energy_match[i] + key_match[i] + speechiness_match[i] + mode_match[i]
            + tempo_match[i] + valence_match[i] + liveness_match[i];
        std::cout << "The match percent of your music taste with profile " << i << " is: " << TOTAL_MATCHUP[i] << std::endl;;
    }

}

void sorting(){
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
        userProfile_check();
        std::cout << "BROSKI, THESE ARE THE PROFILES YOUR MUSIC TASTE MATCHED THE MOST...\n" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "Profile: " <<Profile_names[last_row_id]<< " with match percent" << TOTAL_MATCHUP[i]<<std::endl;
        }
        //closing the database.
        sqlite3_close(db);
}
*/
