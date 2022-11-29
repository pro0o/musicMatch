#ifndef SECOND_PAGE_H
#define SECOND_PAGE_H
#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
//#include "third_page.h"
//#include "calling_api.h"

namespace Ui {
class second_page;
}

class second_page : public QDialog
{
    Q_OBJECT

public:
    explicit second_page(QWidget *parent = nullptr);
    ~second_page();

private slots:
    void on_pushButton_clicked();

private:
    Ui::second_page *ui;
    third_page* third;
};

#endif // SECOND_PAGE_H
