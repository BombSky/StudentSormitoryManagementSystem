#include "mainwindow.h"
//设置列表头
void MainWindow::setFindTableViewHead()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText << "姓 名" << "学 号" << "学生手机号" << "年级" << "班 级" << "班主任" << "辅导员" ;//<< "宿舍等级"
    ui->findTableWidget->setColumnCount(headerText.count());//列数设置为与 headerText的行数相等
    for (int i = 0; i < ui->findTableWidget->columnCount(); i++)
    {
        //cellItem=ui->tableInfo->horizontalHeaderItem(i);
        headerItem = new QTableWidgetItem(headerText.at(i));//新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
        QFont font = headerItem->font();//获取原有字体设置

        font.setBold(true);//设置为粗体
        font.setPixelSize(12);//字体大小
        headerItem->setTextColor("#2E8B57");//字体颜色
//        headerItem->setFont(font);//设置字体
        ui->findTableWidget->setHorizontalHeaderItem(i,headerItem);//设置表头单元格的Item
    }
    addFindTableView();
}

void MainWindow::addFindTableView()
{
    QSqlDatabase db = star_mysql();
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select * from `test_db`.`stulist`");
    if(!query->exec())       qDebug() << "insert fail of addFindTableView";

    QSqlRecord rec = query->record();
    while(query->next())
    {
        query->record();
        ui->findTableWidget->setItem(g_rowCountForFindTableWidget, 0, new QTableWidgetItem(query->value(rec.indexOf(  "stuname"             )).toString()));
        ui->findTableWidget->setItem(g_rowCountForFindTableWidget, 1, new QTableWidgetItem(query->value(rec.indexOf(  "stunumber"           )).toString()));
        ui->findTableWidget->setItem(g_rowCountForFindTableWidget, 2, new QTableWidgetItem(query->value(rec.indexOf(  "stuphone"            )).toString()));
//        ui->findTableWidget->setItem(g_rowCountForFindTableWidget, 3, new QTableWidgetItem(query->value(rec.indexOf(  "addressdormitory"    )).toString()));
        ui->findTableWidget->setItem(g_rowCountForFindTableWidget, 3, new QTableWidgetItem(query->value(rec.indexOf(  "classlevel"          )).toString()));
        ui->findTableWidget->setItem(g_rowCountForFindTableWidget, 4, new QTableWidgetItem(query->value(rec.indexOf(  "classname"           )).toString()));
        ui->findTableWidget->setItem(g_rowCountForFindTableWidget, 5, new QTableWidgetItem(query->value(rec.indexOf(  "headteacher"       )).toString()));
        ui->findTableWidget->setItem(g_rowCountForFindTableWidget, 6, new QTableWidgetItem(query->value(rec.indexOf(  "instructor"          )).toString()));
//        ui->findTableWidget->setItem(g_rowCountForFindTableWidget, 5, new QTableWidgetItem(query->value(rec.indexOf(  "dormitorylevel"      )).toString()));
        g_rowCountForFindTableWidget++;
    }
    g_rowCountForFindTableWidget = 0;
    delete(query);
    db.close();
}

void MainWindow::addNullItemForAddTableWidget()
{
    QSqlDatabase db = star_mysql();
    QSqlQuery *query = new QSqlQuery;
    QSqlQuery *queryforfind = new QSqlQuery;
    QSqlRecord *rec        = new QSqlRecord;
    QSqlRecord *recforfind = new QSqlRecord;
    query               ->prepare("select count(*) AS number from `test_db`.`dorm`");
    queryforfind        ->prepare("select count(*) AS number from `test_db`.`stulist`");
    if(!query           ->exec())       qDebug() << "insert fail of addNullItemForAddTableWidget.dorm        ";
    if(!queryforfind    ->exec())       qDebug() << "insert fail of addNullItemForAddTableWidget.queryforfind";
    *rec        = query         ->record();
    *recforfind = queryforfind  ->record();
    query           ->next();
    queryforfind    ->next();
    for(int i = 0; i < query        ->value(rec       ->indexOf("number")).toInt(); i++)
        ui->addTableWidget    ->insertRow  (0);
    for(int i = 0; i < queryforfind ->value(recforfind->indexOf("number")).toInt(); i++)
        ui->findTableWidget   ->insertRow  (0);
    for(int i = 0; i < query        ->value(rec       ->indexOf("number")).toInt(); i++)
        ui->addormTableWidget ->insertRow  (0);
    db.close();
    delete (query       );
    delete (queryforfind);
}
