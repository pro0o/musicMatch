#include <iostream>
#include <set>

int main()
{   
    std::string _Genres= {"a\nb"};
    const int count_1 = 4;
    const int count_2 = 5;
    std::string a[count_1]= {"a","b","c","d"};
    std::string b[count_2]={"a","c","e","f","g"};

    //setting up set.
    std::set < std::string> s;
    // inserting elements in random order .
    for (int i = 0; i < count_1; i++) {
        s.insert(a[i]);
    }
    for (int i = 0; i < count_2; i++) {
        s.insert(b[i]);
    }

    // printing set s
    //initialising the iterator, iterating to the beginning of the set.
    std::set <std::string >::iterator it;
    _Genres.erase();
    for(it = s.begin(); it != s.end(); it++)
    {   
        _Genres += *it+"\n";
    }
    std::cout << "The element of set s are :"<<std::endl;
    std::cout <<_Genres<< std::endl;
    return 0;
} 