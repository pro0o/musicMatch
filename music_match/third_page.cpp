/*#include "third_page.h"
#include "ui_third_page.h"

third_page::third_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::third_page)
{
    ui->setupUi(this);
}

third_page::~third_page()
{
    delete ui;
}

void third_page::on_pushButton_clicked()
    {
    QString song_name = ui->song_name_bakas->text();
    QString artist_name =ui->artist_name_bakas->text();
    std::string track_name = song_name.toUtf8().constData();
    std::string artist_Name = artist_name.toUtf8().constData();
    if(song_name!="" && artist_name!=""){
                callAPI_artist_name(artist_Name);
                hide();
                fourth = new fourth_page(this);
                fourth->show();
            }
        else QMessageBox::information(this,"","please enter a song name/ artist Name.");

}
*/
