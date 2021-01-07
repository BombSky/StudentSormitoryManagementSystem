#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void login();

signals:
    void showmain();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
