#include "mainwindow.h"
void MainWindow::setMyLineEdit()
{
    ui->stuNumber       ->  setMaxLength(   11  );        //学号限制为11位
    ui->classLevel      ->  setMaxLength(   4   );        //年级限制为两位
    ui->stuPhone        ->  setMaxLength(   11  );        //手机号13位
    QRegExp regExp("[0-9]+$");
    QRegExp dor("^((0([1-9]{1}))|(1[1|2]))/(([0-2]([1-9]{1}))|(3[0|1]))/(d{2}|d{4})$");
    QRegExpValidator *pattern= new QRegExpValidator(regExp, this);//创建了一个表达式
//    QRegExpValidator *pat= new QRegExpValidator(dor, this);//创建了一个表达式
    //交付使用
    ui->stuNumber         ->setValidator(pattern);       //学号限输入制为数字
    ui->classLevel        ->setValidator(pattern);      //班级限输入制为数字
    ui->stuPhone          ->setValidator(pattern);        //学生
    //设置提示内容
    ui->stuName           ->setPlaceholderText("示例：张三");
    ui->stuNumber         ->setPlaceholderText("11位学号");
    ui->stuPhone          ->setPlaceholderText("请输入手机号");
    ui->className         ->setPlaceholderText("示例：软件1班");
    ui->classLevel        ->setPlaceholderText("示例：2018");
    ui->headTeacher       ->setPlaceholderText("班主任名字");
    ui->instructor        ->setPlaceholderText("辅导员名字");
    QStringList qstr_campus;
    QStringList qstr_department;
    QStringList qstr_sex;
    QStringList qstr_buildingno;
    QStringList qstr_floor;
    QStringList qstr_dormitoryno;
    QStringList qstr_dormitorylevel;
    qstr_department     << "计算机工程系" << "土木工程系" << "机电信息系" << "化学工程系" << "经济管理系";
    qstr_campus         << "请选择" << "北校区"      << "南校区";
    qstr_sex            << "请选择" << "男"         << "女";
    qstr_buildingno     << "请选择" << "1栋" << "2栋" << "3栋" << "4栋" << "5栋" << "6栋" << "7栋" << "8栋" << "9栋" << "10栋" << "11栋" << "12栋" << "13栋" << "14栋";
    qstr_floor          << "请选择" << "一层" << "二层" << "三层" << "四层" << "五层" << "六层" << "七层";
    qstr_dormitorylevel << "请选择" << "一级宿舍" << "二级宿舍";
//    qstr_dormitoryno    << ;
    ui->department        ->addItems          (qstr_department      );
    ui->campus            ->addItems          (qstr_campus          );
    ui->sex               ->addItems          (qstr_sex             );
    ui->buildingno        ->addItems          (qstr_buildingno      );
    ui->floor             ->addItems          (qstr_floor           );
    ui->dormitorylevel    ->addItems          (qstr_dormitorylevel  );
}

void MainWindow::setAddTableWidget()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText << "系别" << "校区" << "性别" << "楼号" << "楼层"<< "宿舍号"<< "床位号" << "宿舍级别" << "学 号" << "姓 名" << "学生手机号" << "年级";
    ui->addTableWidget->setColumnCount(headerText.count());//列数设置为与 headerText的行数相等
    for (int i = 0; i < ui->addTableWidget->columnCount(); i++)
    {
        headerItem = new QTableWidgetItem(headerText.at(i));//新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
        QFont font = headerItem->font();//获取原有字体设置
        font.setBold(true);//设置为粗体
        font.setPixelSize(12);//字体大小
        headerItem->setTextColor("#2E8B57");//字体颜色
        ui->addTableWidget->setHorizontalHeaderItem(i,headerItem);//设置表头单元格的Item
    }
    selectDormitoryno();
}

void MainWindow::selectDormitoryno()
{
    ui->addTableWidget->clearContents();
    QSqlDatabase db = star_mysql();
    QSqlQuery *query = new QSqlQuery;

    QString first = "SELECT * FROM test_db.dorm where ";
    QString strdepartment = " department = '" + ui->department->currentText () + "'";
    first += strdepartment;
    QString campus            =                 ui->campus          ->currentText ();
    QString strsex            = QString::number(ui->sex             ->currentIndex());
    QString strbuildingno     = QString::number(ui->buildingno      ->currentIndex());
    QString strfloor          = QString::number(ui->floor           ->currentIndex());
    QString strdormitorylevel = QString::number(ui->dormitorylevel  ->currentIndex());

    if (campus != "请选择"       ) first += (campus            = " and campus         = '" + campus + "'"     );
    if (strsex            != "0") first += (strsex            = " and sex            = "  + strsex           );
    if (strbuildingno     != "0") first += (strbuildingno     = " and buildingno     = "  + strbuildingno    );
    if (strfloor          != "0") first += (strfloor          = " and floor          = "  + strfloor         );
    if (strdormitorylevel != "0") first += (strdormitorylevel = " and dormitorylevel = "  + strdormitorylevel);
    query->prepare(first);

    if(!query->exec())       qDebug() << "insert fail of selectDormitoryno";
    QSqlRecord rec = query->record();
    query->next();
//=================================================================================
    QSqlQuery *querylist = new QSqlQuery;
    QString str1;
    QString str2;
//    str1 = "SELECT * FROM test_db.stulist where stunumber = ";
//    str2 = query->value(rec.indexOf("stunameber")).toString();
//        str1 += str2;
//        qDebug() << str1;
//        querylist->prepare(str1);
//        querylist->exec();
//        QSqlRecord reclist = querylist->record();
//        querylist->next();
//        qDebug() << querylist->value(reclist.indexOf("stuname"));
//        str2 = querylist->value(reclist.indexOf("stuname")).toString();

//=================================================================================

    do{
//        query->record();
//=================================================================================
        str1 = "SELECT * FROM test_db.stulist where stunumber = ";
        str2 = query->value(rec.indexOf("stunameber")).toString();
        str1 += str2;
        querylist->prepare(str1);
        querylist->exec();
        QSqlRecord reclist = querylist->record();
        querylist->next();
//=================================================================================
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 0, new QTableWidgetItem(                    query->value(rec.indexOf("department"    )).toString()));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 1, new QTableWidgetItem(                    query->value(rec.indexOf("campus"        )).toString()));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 2, new QTableWidgetItem(g_CHSex            [query->value(rec.indexOf("sex"           )).toInt  ()]));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 3, new QTableWidgetItem(g_CHBuildingno     [query->value(rec.indexOf("buildingno"    )).toInt  ()]));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 4, new QTableWidgetItem(g_CHFloor          [query->value(rec.indexOf("floor"         )).toInt  ()]));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 5, new QTableWidgetItem(                    query->value(rec.indexOf("dormitoryno"   )).toString()));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 6, new QTableWidgetItem(g_CHBedno          [query->value(rec.indexOf("bedno"         )).toInt  ()]));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 7, new QTableWidgetItem(g_CHDormitorylevel [query->value(rec.indexOf("dormitorylevel")).toInt  ()]));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 8, new QTableWidgetItem(query->value(rec.indexOf(  "stunameber"  )).toString()));
        //学生表的内容
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 9, new QTableWidgetItem(querylist->value(reclist.indexOf("stuname")).toString()));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 10,new QTableWidgetItem(querylist->value(reclist.indexOf(  "stuphone"    )).toString()));
        ui->addTableWidget->setItem(g_rowCountForAddTableWidget, 11,new QTableWidgetItem(querylist->value(reclist.indexOf(  "classlevel"  )).toString()));
        g_rowCountForAddTableWidget++;
    }while(query->next());
    g_rowCountForAddTableWidget = 0;
    delete(query);
    db.close();
}

QString MainWindow::dormid()
{
//    QSqlDatabase db = star_mysql();
    //获取内容
    QString stuname           (     ui->stuName           ->text()              );  //姓名
    QString stunumber         (     ui->stuNumber         ->text()              );  //学号
    QString stuphone          (     ui->stuPhone          ->text()              );  //手机号
    QString classname         (     ui->className         ->text()              );  //班级
//    int     classlevel        (     ui->classLevel        ->text().toInt()      );  //年级
    QString headteacher       (     ui->headTeacher       ->text()              );  //班主任
    QString instructor        (     ui->instructor        ->text()              );  //辅导员

    QString department        (     ui->department        ->currentText ()      );  //系别
    QString campus            (     ui->campus            ->currentText ()      );  //校区
    int     sex               (     ui->sex               ->currentIndex()      );  //性别
    int     buildingno        (     ui->buildingno        ->currentIndex()      );  //楼号
    int     floor             (     ui->floor             ->currentIndex()      );  //楼层
    int     dormitorylevel    (     ui->dormitorylevel    ->currentIndex()      );  //宿舍级别
    int     dormitoryno       (     ui->dormitoryno       ->text().toInt()      );  //宿舍号
    int     bedno             (     ui->bedno             ->text().toInt()      );  //床位号
    QSqlQuery *query        = new QSqlQuery;
    QString first = "SELECT * FROM test_db.dorm where ";
    if (department != "请选择") first += (" department         = '" + department + "'"               );
    if (campus     != "请选择") first += (" and campus         = '" + campus + "'"                   );
    if (sex            != 0)   first += (" and sex            = "  + QString::number(sex           ));
    if (buildingno     != 0)   first += (" and buildingno     = "  + QString::number(buildingno    ));
    if (floor          != 0)   first += (" and floor          = "  + QString::number(floor         ));
    if (dormitorylevel != 0)   first += (" and dormitorylevel = "  + QString::number(dormitorylevel));
    if (dormitoryno    != NULL)first += (" and dormitoryno    = "  + QString::number(dormitoryno   ));
    if (bedno          != NULL)first += (" and bedno          = "  + QString::number(bedno         ));
    query->prepare(first);
    if(!query->exec())       qDebug() << "insert fail for dormid";

    QSqlRecord rec = query->record();
    query->next();
    query->record();
    QString re = query->value(rec.indexOf("id")).toString();
    delete(query);
//    db.close();
    return re;
}

void MainWindow::addPutIn()
{
    QSqlDatabase db = star_mysql();
    //获取内容
    QString stuname           (     ui->stuName           ->text()              );  //姓名
    QString stunumber         (     ui->stuNumber         ->text()              );  //学号
    QString stuphone          (     ui->stuPhone          ->text()              );  //手机号
    QString classname         (     ui->className         ->text()              );  //班级
    int     classlevel        (     ui->classLevel        ->text().toInt()      );  //年级
    QString headteacher       (     ui->headTeacher       ->text()              );  //班主任
    QString instructor        (     ui->instructor        ->text()              );  //辅导员

    QString department        (     ui->department        ->currentText ()      );  //系别
    QString campus            (     ui->campus            ->currentText ()      );  //校区
    int     sex               (     ui->sex               ->currentIndex()      );  //性别
    int     buildingno        (     ui->buildingno        ->currentIndex()      );  //楼号
    int     floor             (     ui->floor             ->currentIndex()      );  //楼层
    int     dormitorylevel    (     ui->dormitorylevel    ->currentIndex()      );  //宿舍级别
    int     dormitoryno       (     ui->dormitoryno       ->text().toInt()      );  //宿舍号
    int     bedno             (     ui->bedno             ->text().toInt()      );  //床位号
    QSqlQuery *query        = new QSqlQuery;
    QSqlQuery *queryfordorm = new QSqlQuery;
    QString strno = dormid();
    QString str = "UPDATE `test_db`.`dorm` SET `stunameber` = '" + stunumber + "' WHERE (`id` = '"+dormid()+"')";

//stulist
    query->prepare("INSERT INTO `test_db`.`stulist` (\
    `stuname`, `stunumber`, `stuphone`, `classname`, `department`,\
    `headteacher`, `instructor`, `classlevel`, `campus`,\
    `sex`) VALUES (?,?,?,?,?,?,?,?,?,?)");
//dorm
    queryfordorm->prepare(str);
//stulist
    query->bindValue(0 , QString    (   stuname        ));
    query->bindValue(1 , QString    (   stunumber      ));
    query->bindValue(2 , QString    (   stuphone       ));
    query->bindValue(3 , QString    (   classname      ));
    query->bindValue(4 , QString    (   department     ));
    query->bindValue(5 , QString    (   headteacher    ));
    query->bindValue(6 , QString    (   instructor     ));
    query->bindValue(7 , int        (   classlevel     ));
    query->bindValue(8 , QString    (   campus         ));
    query->bindValue(9 , int        (   sex            ));
//dorm
    queryfordorm->bindValue(0 , QString    (   stunumber           ));
    queryfordorm->bindValue(1 , int        (   buildingno          ));
    queryfordorm->bindValue(2 , int        (   floor               ));
    queryfordorm->bindValue(3 , int        (   dormitoryno         ));
    queryfordorm->bindValue(4 , int        (   bedno               ));
    queryfordorm->bindValue(5 , QString    (   campus              ));
    queryfordorm->bindValue(6 , int        (   sex                 ));
    queryfordorm->bindValue(7 , int        (   dormitorylevel      ));
    queryfordorm->bindValue(8 , QString    (   department          ));
    if(!query       ->exec())       qDebug() << "insert fail for addPutIn.query";
    if(!queryfordorm->exec())       qDebug() << "insert fail for addPutIn.queryfordorm";
    delete (query       );
    delete (queryfordorm);
    addPageClear();
    db.close();
    selectDormitoryno();
}
void MainWindow::on_department_activated    (const QString &arg1)       {    selectDormitoryno(); arg1+1;    }
void MainWindow::on_campus_activated        (const QString &arg1)       {    selectDormitoryno(); arg1+1;    }
void MainWindow::on_sex_activated           (const QString &arg1)       {    selectDormitoryno(); arg1+1;    }
void MainWindow::on_buildingno_activated    (const QString &arg1)       {    selectDormitoryno(); arg1+1;    }
void MainWindow::on_floor_activated         (const QString &arg1)       {    selectDormitoryno(); arg1+1;    }
void MainWindow::on_dormitorylevel_activated(const QString &arg1)       {    selectDormitoryno(); arg1+1;    }
void MainWindow::addPageClear()
{
    ui->stuName           ->clear();
    ui->stuNumber         ->clear();
    ui->stuPhone          ->clear();
    ui->className         ->clear();
    ui->classLevel        ->clear();
    ui->headTeacher       ->clear();
    ui->instructor        ->clear();
    ui->dormitoryno       ->clear();
    ui->bedno             ->clear();
}

//void MainWindow::modifyStu()
//{
//    QSqlDatabase db = star_mysql();
//    QSqlQuery *query        = new QSqlQuery;
//    //获取内容
//    QString stuname           (     ui->stuName           ->text()              );  //姓名
//    QString stunumber         (     ui->stuNumber         ->text()              );  //学号
//    QString stuphone          (     ui->stuPhone          ->text()              );  //手机号
//    QString classname         (     ui->className         ->text()              );  //班级
//    int     classlevel        (     ui->classLevel        ->text().toInt()      );  //年级
//    QString headteacher       (     ui->headTeacher       ->text()              );  //班主任
//    QString instructor        (     ui->instructor        ->text()              );  //辅导员

//    QString department        (     ui->department        ->currentText ()      );  //系别
//    QString campus            (     ui->campus            ->currentText ()      );  //校区
//    int     sex               (     ui->sex               ->currentIndex()      );  //性别
////    int     buildingno        (     ui->buildingno        ->currentIndex()    );  //楼号
////    int     floor             (     ui->floor             ->currentIndex()    );  //楼层
////    int     dormitorylevel    (     ui->dormitorylevel    ->currentIndex()    );  //宿舍级别
////    int     dormitoryno       (     ui->dormitoryno       ->text().toInt()      );  //宿舍号
////    int     bedno             (     ui->bedno             ->text().toInt()      );  //床位号
//    query->prepare("UPDATE `test_db`.`dorm` SET `stunameber` = '111111111111' WHERE (`id` = '201')");
//    if(!query->exec())       qDebug() << "insert fail for addPutIn.queryfordorm";
//    delete (query       );
//    db.close();
//}
