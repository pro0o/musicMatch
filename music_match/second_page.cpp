/*
#include "second_page.h"
#include "ui_second_page.h"

second_page::second_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::second_page)
{
    ui->setupUi(this);
}

second_page::~second_page()
{
    delete ui;
}

void second_page::on_pushButton_clicked()
{
    QString song_name = ui->song_name_bakas->text();
    QString artist_name =ui->artist_name_bakas->text();
    std::string track_name = song_name.toUtf8().constData();
    std::string artist_Name = artist_name.toUtf8().constData();
    if(song_name!="" && artist_name!=""){
        callAPI_trackname_af(track_name, artist_Name);
        hide();
        //third = new third_page(this);
        //third->show();
    }
    else QMessageBox::information(this,"","please enter a song name/ artist Name.");
}
*/
