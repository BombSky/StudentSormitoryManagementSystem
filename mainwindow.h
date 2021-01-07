#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <qvalidator.h>
#include <QDebug>
#include <list>
#include <QLineEdit>
#include <QBrush>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlRecord>
#include <QComboBox>
#include <QMouseEvent>
#include <QApplication>
#include <string>
#include "ui_mainwindow.h"
#include "dialog.h"
QSqlDatabase star_mysql();
using namespace std;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setMyLineEdit();
    void deletLineEdit();
    void addPageClear();
    void setFindTableViewHead();
    void addFindTableView();
    void selectDormitoryno();
    void setAddTableWidget();
    void addNullItemForAddTableWidget();
    int g_rowCountForAddTableWidget     = 0;
    int g_rowCountForFindTableWidget    = 0;
    QString g_CHSex           [3 ]  = {"","男", "女"};
    QString g_CHBuildingno    [15]  = {"","一栋","二栋","三栋","四栋","五栋","六栋","七栋","八栋","九栋","十栋","十一栋","十二栋","十三栋","十四栋"};
    QString g_CHFloor         [8 ]  = {"","一楼","二楼","三楼","四楼","五楼","六楼","七楼"};
    QString g_CHDormitorylevel[3 ]  = {"","一级宿舍","二级宿舍"};
    QString g_CHBedno         [9 ]  = {"","1号铺","2号铺","3号铺","4号铺","5号铺","6号铺","7号铺","8号铺"};
    //addorm.h
    void setAddormWidget();
    void checkout(QString *stuno);
    int g_rowCountForAddormTableWidget  = 0;
    QString g_qstr_deletDorm = " ";
    QString dormid();

private slots:
    void switchPage();
    void addPutIn();
    void setAddormPutIn();
    void addormFindList();
    void on_department_activated(const QString &arg1);
    void on_campus_activated(const QString &arg1);
    void on_sex_activated(const QString &arg1);
    void on_buildingno_activated(const QString &arg1);
    void on_floor_activated(const QString &arg1);
    void on_dormitorylevel_activated(const QString &arg1);
    void addormDelete();
//    void modifyStu();
    void deletestu();
    void deletefindstu();
    void receivelogin();
    void onlyleftout();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
