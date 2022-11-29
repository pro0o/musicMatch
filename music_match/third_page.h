#ifndef THIRD_PAGE_H
#define THIRD_PAGE_H
#include <QDialog>
//#include "calling_api.h"
#include <QMainWindow>

#include <QMessageBox>
//#include "fourth_page.h"
namespace Ui {
class third_page;
}

class third_page : public QDialog
{
    Q_OBJECT

public:
    explicit third_page(QWidget *parent = nullptr);
    ~third_page();

private slots:
    void on_pushButton_clicked();

private:
    Ui::third_page *ui;
    //fourth_page *fourth;
};

#endif // THIRD_PAGE_H

