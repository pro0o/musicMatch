#include "fourth_page.h"
#include "ui_fourth_page.h"

fourth_page::fourth_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fourth_page)
{
    ui->setupUi(this);
}

fourth_page::~fourth_page()
{
    delete ui;
}

void fourth_page::on_pushButton_clicked()
{
    QString artist_name_1 =ui->artist_name_bakas_1->text();
    std::string artist_Name_1 = artist_name_1.toUtf8().constData();
    QString artist_name_2 =ui->artist_name_bakas_2->text();
    std::string artist_Name_2 = artist_name_2.toUtf8().constData();
    QString artist_name_3 =ui->artist_name_bakas_3->text();
    std::string artist_Name_3 = artist_name_3.toUtf8().constData();
    if(artist_Name_1!="" && artist_Name_2!="" && artist_Name_3!=""){
                callAPI_artist_name(artist_Name_1);
                callAPI_artist_name(artist_Name_2);
                callAPI_artist_name(artist_Name_3);
                //_add_up();
                hide();
                last = new last_page(this);
                last->show();
            }
        else QMessageBox::information(this,"","please enter artist Name.");
}

