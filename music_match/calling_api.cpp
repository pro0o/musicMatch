/*
#include "calling_api.h"

//token from spotify.
const std::string TOKEN = "";

std::string username="";
//global variables.
double feature_af[9] = {};

std::string _Genres;

void userName(std::string name){
username = name;
}

//call api for audio features.
void callAPI_audiofeatures(std::string track_id, std::string artistname) {
    std::string URI = "https://api.spotify.com/v1/audio-features/";
    URI += track_id;
    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    std::cout << '\n' << '\n' << "Again, calling an api request for AUDIO FEATURES using retreived unique track id." <<std:: endl;

    switch (r.status_code) {
    case 200:
        std::cout << "THE REQUEST WAS SUCEEDED." << std::endl;
        break;
    case 400:
        std::cout << "INVALID REQUEST." << std::endl;
        break;
    case 404:
        std::cout << "THE TOKEN HAS EXPIRED." << std::endl;
        break;
    case 429:
        std::cout << "Too Many Requests - Rate limiting has been applied by the SPOTIFY SERVER." << std::endl;
        break;
    }

    //Now getting features.
    std::string feature[9] = { "acousticness", "danceability", "energy", "key", "speechiness", "mode", "tempo", "valence", "liveness" };
    for (int i = 0; i < 9; i++) {
        std::string parameter = get_audiofeatures(r.text, feature[i]);
        //convert string into double.
        feature_af[i] = stod(parse(parameter));
       std:: cout << "the " << feature[i] << " of the song is : " << feature_af[i] << std::endl;
    }
}

void callAPI_GENRE(std::string artist_id) {

    std::string URI = "https://api.spotify.com/v1/artists/";
    URI = URI + artist_id;
    std::cout << URI;
    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    std::cout << '\n' << "NOW AGAIN, REQUESTING API FOR GENRES WITH THE RETRIEVED UNIQUE ARTIST ID." << '\n';

    switch (r.status_code) {
    case 200:
        std::cout << "THE API REQUEST WAS SUCEEDED." << std::endl;
        break;
    case 400:
        std::cout << "INVALID REQUEST." << std::endl;
        break;
    case 404:
        std::cout << "THE TOKEN HAS EXPIRED." << std::endl;
        break;
    case 429:
        std::cout << "Too Many Requests - Rate limiting has been applied by the SPOTIFY SERVER." <<std:: endl;
        break;
    }
    std::string genres = getgenres(r.text);

    //check if the same genre exists or not...
    if (_Genres == "")_Genres += genres;

    else{
        //a is a temp string.
        std::string a;
        //creating an array that stores separate genre distinguished by newline.

        //ffs count_1/count_2 important affffff.
        //count_1/count_2 increases by 1 if any new line or last element is met and later on determines the size of array with genres filled.
        int count_1 = 0;
        std::string genre_array_1[15] = {};
        //if a character is new line or last element of string, then count is added by 1 and until new line string is added in array.
        for (int i = 0; i <= _Genres.size(); i++) {
            if (_Genres[i] == '\n' || _Genres[i] == _Genres[_Genres.size()]) {
                count_1++;
                genre_array_1[count_1 - 1] = a;
                a.erase(0, a.size());
            }
            else a += _Genres[i];

        }
        std::cout << "\n" << count_1 << " datas were stored in genres array:" << std::endl;
        for (int i = 0; i < count_1; i++) {
            std::cout << i << " " << genre_array_1[i] << std::endl;
        }

        std::string genre_array_2[15] = {};
        int count_2 = 0;
        for (int i = 0; i <= genres.size(); i++) {
            if (genres[i] == '\n' || genres[i] == genres[genres.size()]) {
                count_2++;
                genre_array_2[count_2 - 1] = a;
                a.erase(0, a.size());
            }
            else a += genres[i];
        }

        std::cout << count_2 << " datas were stored in genre 1 array:" << std::endl;
        for (int i = 0; i < count_2; i++) {
            std::cout << i << " " << genre_array_2[i] << std::endl;
        }
        //bubble sort now.
        for (int i = 0; i < count_1; i++) {
            for (int j = 0; j < count_2; j++) {
               std:: string genre1 = genre_array_1[i];
               std:: string genre2 = genre_array_2[j];
                if (genre1 != genre2) {
                    _Genres += "\n" + genre2;
                }
            }
        }
        std::cout << "genres stored in this session are:" << _Genres << std::endl;
    }
}

//call spotify api with trackname and artist name (3rd question)
void callAPI_artist_name(std::string artistName) {

    std::string URI = "https://api.spotify.com/v1/search?q=";
    URI = URI + parse_shit(artistName);
    URI = URI + "&type=artist&limit=1";
    std::cout << URI;

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    std::cout << "\n" << "ARTIST INFO:" << std::endl;
    std::cout << "calling an api request to retrieve artist id." << '\n';

    switch (r.status_code) {
    case 200:
        std::cout << "THE REQUEST WAS SUCEEDED." << std::endl;
        break;
    case 400:
        std::cout << "INVALID REQUEST." << std::endl;
        break;
    case 404:
        std::cout << "THE TOKEN HAS EXPIRED." << std::endl;
        break;
    case 429:
        std::cout << "Too Many Requests - Rate limiting has been applied by the SPOTIFY SERVER." <<std::endl;
        break;
    }
    std::string artist_id = getartistid(r.text);
    std::cout << "THE ARTIST ID IS: " << artist_id << std::endl;
    callAPI_GENRE(artist_id);
}

//call api with inputed track name.
void callAPI_trackname_af(std::string trackname, std::string artistname) {
    std::string URI = "https://api.spotify.com/v1/search?q=";
    URI += parse_shit(trackname);
    URI += "+" + parse_shit(artistname);
    URI += "&type=track&limit=1";
    std::cout<<URI;

    cpr::Response r = cpr::Get(cpr::Url{ URI }, cpr::Bearer{ TOKEN });
    std::cout << "\n" << "TRACK INFO:" << std::endl;
    std::cout << "calling an api request to retrieve track id." << std::endl;

    switch (r.status_code) {
    case 200:
        std::cout << "THE API REQUEST WAS SUCEEDED." << std::endl;
        break;
    case 400:
        std::cout << "INVALID REQUEST." << std::endl;
        break;
    case 404:
        std::cout << "INVALID REQUEST." << std::endl;
        break;
    case 401:
        std::cout << "THE TOKEN HAS EXPIRED." << std::endl;
        break;
    case 429:
        std::cout << "Too Many Requests - Rate limiting has been applied by the SPOTIFY SERVER." << std::endl;
        break;
    }
    std::string track_id = parse(get_trackid(r.text));
    std::cout << "the track id is: " << track_id;
    callAPI_audiofeatures(track_id, artistname);
    callAPI_artist_name(artistname);

}

void _add_up(){
    adding_up(username, feature_af[0], feature_af[1], feature_af[2], int(feature_af[3]), feature_af[4], int(feature_af[5]), feature_af[6], feature_af[7], feature_af[8], _Genres);
}
*/
