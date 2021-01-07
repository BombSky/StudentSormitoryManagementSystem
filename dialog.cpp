#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
QSqlDatabase star_mysql();

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lepassword->setEchoMode(QLineEdit::Password);
    connect(ui->btnlogin    ,&QPushButton::clicked, this, &Dialog::login);
    connect(ui->pushButton_2,&QPushButton::clicked, this, &Dialog::close);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::login()
{
    QSqlDatabase db = star_mysql();
    QSqlQuery *query  = new QSqlQuery;
    QString *str = new QString("select * from test_db.user where username = '");
    QString *username = new QString;
    QString *struserpass = new QString(ui->lepassword->text());
    *username = ui->leid->text();
    *str += (*username + "'");
    query->prepare(*str);
    if(!query->exec())       qDebug() << "insert fail of login";
    QSqlRecord rec = query->record();
    query->next();
    QString *strdbuserpass = new QString(query->value(rec.indexOf("userpassword")).toString());
    if(*struserpass == *strdbuserpass)
    {
        this->hide();
        emit showmain();
    }
    delete(query);
    db.close();
}

