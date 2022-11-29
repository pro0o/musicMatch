//#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <cpr/cpr.h>
#include "sqlite/sqlite3.h"


int main(int argc, char *argv[])
{
    /*
    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
                                   cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                                   cpr::Parameters{{"anon", "true"}, {"key", "value"}});
        std::cout << "Status code: " << r.status_code << '\n';
        std::cout << "Header:\n";
        for (const std::pair<const std::basic_string<char>, std::basic_string<char>>& kv : r.header) {
            std::cout << '\t' << kv.first << ':' << kv.second << '\n';
        }
        std::cout << "Text: " << r.text << '\n';
            */
    QApplication a(argc, argv);
    //MainWindow w;
    w.show();
    return a.exec();
}
