#include "last_page.h"
#include "ui_last_page.h"

last_page::last_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::last_page)
{
    ui->setupUi(this);
}

last_page::~last_page()
{   //comparing every stored datas from database.
    std::cout << "\nCOMPARING RETRIEVED DATAS FROM YOU TO ALL OTHER AVAILABLE PROFILES..." << std::endl;
    /*
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
    _total_match_up();
    sorting();
    */
    delete ui;
}
