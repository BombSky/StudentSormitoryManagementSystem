#include "mainwindow.h"


void MainWindow::setAddormWidget()
{
    QStringList addormbuilno;
    QStringList adddormfloor;
    QStringList addormcampus;
    QStringList addormdepar ;
    QStringList addormlevel ;
    QStringList addormsex   ;
    addormbuilno << "请选择" << "1栋" << "2栋" << "3栋" << "4栋" << "5栋" << "6栋" << "7栋" << "8栋" << "9栋" << "10栋" << "11栋" << "12栋" << "13栋" << "14栋";
    adddormfloor << "请选择" << "一层" << "二层" << "三层" << "四层" << "五层" << "六层" << "七层";
    addormcampus << "请选择" << "北校区"      << "南校区";
    addormdepar  << "计算机工程系" << "土木工程系" << "机电信息系" << "化学工程系" << "经济管理系";
    addormlevel  << "请选择" << "一级宿舍" << "二级宿舍";
    addormsex    << "请选择" << "男"         << "女";

    QRegExp regExp("[0-9]+$");
    QRegExpValidator *pattern= new QRegExpValidator(regExp, this);//创建了一个表达式
    ui->addormno    ->setValidator(pattern);

    ui->addormbuilno->addItems(addormbuilno);
    ui->adddormfloor->addItems(adddormfloor);
    ui->addormcampus->addItems(addormcampus);
    ui->addormdepar ->addItems(addormdepar );
    ui->addormlevel ->addItems(addormlevel );
    ui->addormsex   ->addItems(addormsex   );
    ui->addormno    ->setPlaceholderText("请输入该层宿舍的数量");
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText << "楼号" << "楼层" << "校区" << "系别" << "宿舍级别" << "宿舍号" << "床位号" << "性别";
    ui->addormTableWidget->setColumnCount(headerText.count());//列数设置为与 headerText的行数相等
    for (int i = 0; i < ui->addormTableWidget->columnCount(); i++)
    {
        headerItem = new QTableWidgetItem(headerText.at(i));//新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
        QFont font = headerItem->font();//获取原有字体设置
        font.setBold(true);//设置为粗体
        font.setPixelSize(12);//字体大小
        headerItem->setTextColor("#2E8B57");//字体颜色
        ui->addormTableWidget->setHorizontalHeaderItem(i,headerItem);//设置表头单元格的Item
    }
}
void MainWindow::setAddormPutIn()
{
    QSqlDatabase db = star_mysql();
    QSqlQuery *query  = new QSqlQuery;
    query->prepare("INSERT INTO `test_db`.`dorm` (\
    `buildingno`, `floor`, `dormitoryno`, `bedno`, \
    `campus`, `sex`, `dormitorylevel`, `department`) \
    VALUES (?,?,?,?,?,?,?,?);");
    int bedno = 8;
    QString bedNoOutPut = "此处折叠8个床位";
    if (1 == ui->addormlevel ->currentIndex())
    {
        bedno = 6;
        bedNoOutPut = "此处折叠6个床位";
    }
    int rowcount = ui->addormTableWidget->rowCount();
    for(int i = 1; i <= ui->addormno->text().toInt(); i++)
    {
        for(int j = 1; j <= bedno; j++)
        {
            query->bindValue(0 , int        (   ui->addormbuilno->currentIndex()    ));
            query->bindValue(1 , int        (   ui->adddormfloor->currentIndex()    ));
            query->bindValue(2 , int        (   i                                   ));
            query->bindValue(3 , int        (   j                                   ));
            query->bindValue(4 , QString    (   ui->addormcampus->currentText ()    ));
            query->bindValue(5 , int        (   ui->addormsex   ->currentIndex()    ));
            query->bindValue(6 , int        (   ui->addormlevel ->currentIndex()    ));
            query->bindValue(7 , QString    (   ui->addormdepar ->currentText ()    ));
            if(!query       ->exec())       qDebug() << "insert fail for addPutIn.query";
        }
        ui->addormTableWidget->insertRow  (rowcount);
        ui->addormTableWidget->setItem(rowcount, 0, new QTableWidgetItem(g_CHBuildingno    [ui->addormbuilno->currentIndex()]));
        ui->addormTableWidget->setItem(rowcount, 1, new QTableWidgetItem(g_CHFloor         [ui->adddormfloor->currentIndex()]));
        ui->addormTableWidget->setItem(rowcount, 2, new QTableWidgetItem(                   ui->addormcampus->currentText () ));
        ui->addormTableWidget->setItem(rowcount, 3, new QTableWidgetItem(                   ui->addormdepar ->currentText () ));
        ui->addormTableWidget->setItem(rowcount, 4, new QTableWidgetItem(g_CHDormitorylevel[ui->addormlevel ->currentIndex()]));
        ui->addormTableWidget->setItem(rowcount, 5, new QTableWidgetItem(QString::number(i)                                  ));
        ui->addormTableWidget->setItem(rowcount, 6, new QTableWidgetItem(bedNoOutPut                                         ));
        ui->addormTableWidget->setItem(rowcount, 7, new QTableWidgetItem(g_CHSex           [ui->addormsex   ->currentIndex()]));
    }

    delete(query);
    db.close();
    addormFindList();
}

void MainWindow::addormFindList()
{
    ui->addormTableWidget->clearContents();
    QSqlDatabase db = star_mysql();
    QSqlQuery *query  = new QSqlQuery;
    QString first = "SELECT * FROM test_db.dorm where ";
    QString addormdepar = " department = '" + ui->addormdepar->currentText () + "'";
    first += addormdepar;
    g_qstr_deletDorm = " department = '" + ui->addormdepar->currentText () + "'";
    QString addormbuilno = QString::number(ui->addormbuilno ->currentIndex());
    QString adddormfloor = QString::number(ui->adddormfloor ->currentIndex());
    QString addormcampus = ui->addormcampus ->currentText();
    QString addormsex    = QString::number(ui->addormsex    ->currentIndex());
    QString addormlevel  = QString::number(ui->addormlevel  ->currentIndex());

    if (addormbuilno != "0" )
    {
        g_qstr_deletDorm += (" and buildingno = " + addormbuilno    );
        first            += (addormbuilno = " and buildingno = " + addormbuilno    );
    }
    if (adddormfloor != "0" )
    {
        g_qstr_deletDorm += (" and floor = " + adddormfloor         );
        first +=            (adddormfloor = " and floor = " + adddormfloor         );
    }
    if (addormcampus != "请选择" )
    {
        g_qstr_deletDorm += (" and campus = '" + addormcampus  + "'"        );
        first +=            (addormcampus = " and campus = '" + addormcampus + "'" );
        qDebug() << first;
    }
    if (addormsex    != "0" )
    {
        g_qstr_deletDorm += (" and sex    = " + addormsex           );
        first +=            (addormsex    = " and sex    = " + addormsex           );
    }
    if (addormlevel  != "0" )
    {
        g_qstr_deletDorm += (" and dormitorylevel  = " + addormlevel);
        first +=            (addormlevel  = " and dormitorylevel  = " + addormlevel);
    }
    query->prepare(first);
//    qDebug() << g_qstr_deletDorm;
    if(!query->exec())       qDebug() << "insert fail of selectDormitoryno";
    QSqlRecord rec = query->record();
//    int rowcount = ui->addormTableWidget->rowCount();
    while(query->next())
    {
        query->record();
//        ui->addormTableWidget->insertRow  (rowcount);
        ui->addormTableWidget->setItem(g_rowCountForAddormTableWidget, 0, new QTableWidgetItem(g_CHBuildingno       [query->value(rec.indexOf(  "buildingno"        )).toInt   ()]));
        ui->addormTableWidget->setItem(g_rowCountForAddormTableWidget, 1, new QTableWidgetItem(g_CHFloor            [query->value(rec.indexOf(  "floor"             )).toInt   ()]));
        ui->addormTableWidget->setItem(g_rowCountForAddormTableWidget, 2, new QTableWidgetItem(                      query->value(rec.indexOf(  "campus"            )).toString()));
        ui->addormTableWidget->setItem(g_rowCountForAddormTableWidget, 3, new QTableWidgetItem(                      query->value(rec.indexOf(  "department"        )).toString()));
        ui->addormTableWidget->setItem(g_rowCountForAddormTableWidget, 4, new QTableWidgetItem(g_CHDormitorylevel   [query->value(rec.indexOf(  "dormitorylevel"    )).toInt   ()]));
        ui->addormTableWidget->setItem(g_rowCountForAddormTableWidget, 5, new QTableWidgetItem(                      query->value(rec.indexOf(  "dormitoryno"       )).toString()));
        ui->addormTableWidget->setItem(g_rowCountForAddormTableWidget, 6, new QTableWidgetItem(g_CHBedno            [query->value(rec.indexOf(  "bedno"             )).toInt   ()]));
        ui->addormTableWidget->setItem(g_rowCountForAddormTableWidget, 7, new QTableWidgetItem(g_CHSex              [query->value(rec.indexOf(  "sex"               )).toInt   ()]));
        g_rowCountForAddormTableWidget++;
    }
    g_rowCountForAddormTableWidget = 0;

    delete(query);
    db.close();
}

void MainWindow::addormDelete()
{
    QSqlDatabase db = star_mysql();
    QSqlQuery *query  = new QSqlQuery;
    //g_qstr_deletDorm
    QString *str = new QString;
    *str = "DELETE FROM test_db.dorm where ";
    *str += g_qstr_deletDorm;
    query->prepare(*str);
    qDebug() << *str;
    if(!query->exec())       qDebug() << "insert fail of selectDormitoryno";
    delete(str);
    delete(query);
    db.close();
    addormFindList();
}

//void MainWindow::cleardorm()
//{
//    QSqlDatabase db = star_mysql();
//    QSqlQuery *query  = new QSqlQuery;
//    QString *str = new QString;
//    QString *stuno = new QString;
//    *str = "select * FROM test_db.dorm where ";
//    *str += g_qstr_deletDorm;
//    query->prepare(*str);
//    qDebug() << *str;
//    if(!query->exec())       qDebug() << "insert fail of selectDormitoryno";
//    QSqlRecord rec = query->record();
//    while(query->next()) {
//        *stuno = query->value(rec.indexOf("stunameber")).toString();
//        checkout(stuno);
//    }
//    delete(str);
//    delete(query);
//    db.close();
//}
