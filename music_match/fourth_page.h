/*
#ifndef FOURTH_PAGE_H
#define FOURTH_PAGE_H

#include <QDialog>
#include "last_page.h"
#include "calling_api.h"
#include <QMainWindow>
#include <QMessageBox>
#include "database.h"


namespace Ui {
class fourth_page;
}

class fourth_page : public QDialog
{
    Q_OBJECT

public:
    explicit fourth_page(QWidget *parent = nullptr);
    ~fourth_page();

private slots:
    void on_pushButton_clicked();

private:
    Ui::fourth_page *ui;
    last_page *last;
};


#endif // FOURTH_PAGE_H
*/
