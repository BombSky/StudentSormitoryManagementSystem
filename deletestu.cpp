#include"mainwindow.h"
void MainWindow::deletestu()
{
    QSqlDatabase db = star_mysql();
    QSqlQuery *query  = new QSqlQuery;
    QString *ledeletestuno = new QString;
    QString *strdeletequery = new QString;
    *ledeletestuno = ui->ledeletestuno->text();
//    *strdeletequery = "DELETE FROM test_db.dorm where stunameber = " + *ledeletestuno;
    *strdeletequery = "SELECT * FROM test_db.dorm where stunameber = " + *ledeletestuno;
    query->prepare(*strdeletequery);
    if(!query->exec())       qDebug() << "insert fail of deletestu.dorm";
    QSqlRecord rec = query->record();
    query->next();
    query->record();
    *strdeletequery = "UPDATE test_db.dorm set stunameber = null where id = " + query->value(rec.indexOf("id")).toString();
    query->prepare(*strdeletequery);
    if(!query->exec())       qDebug() << "insert fail of deletestu.dorm";



    *strdeletequery = "DELETE FROM test_db.stulist where stunumber = " + *ledeletestuno;
    query->prepare(*strdeletequery);
    if(!query->exec())       qDebug() << "insert fail of deletestu.dorm";
    delete(strdeletequery);
    delete(ledeletestuno);
    delete(query);
    db.close();
//    ui->label_25->setText("hello");
    deletefindstu();
}
void MainWindow::onlyleftout()
{
    QSqlDatabase db = star_mysql();
    QSqlQuery *query  = new QSqlQuery;
    QString *ledeletestuno = new QString;
    QString *strdeletequery = new QString;
    *ledeletestuno = ui->ledeletestuno->text();
//    *strdeletequery = "DELETE FROM test_db.dorm where stunameber = " + *ledeletestuno;
    *strdeletequery = "SELECT * FROM test_db.dorm where stunameber = " + *ledeletestuno;
    query->prepare(*strdeletequery);
    if(!query->exec())       qDebug() << "insert fail of deletestu.dorm";
    QSqlRecord rec = query->record();
    query->next();
    query->record();
    *strdeletequery = "UPDATE test_db.dorm set stunameber = null where id = " + query->value(rec.indexOf("id")).toString();
    query->prepare(*strdeletequery);
    if(!query->exec())       qDebug() << "insert fail of deletestu.dorm";
    delete(ledeletestuno);
    delete(query);
    db.close();
    deletefindstu();
}
void MainWindow::deletefindstu()
{
    QSqlDatabase db = star_mysql();
    QSqlQuery *query  = new QSqlQuery;
    QString *dbtextfirst = new QString;
    *dbtextfirst = "select * from test_db.stulist where stunumber = " + ui->ledeletestuno->text();
//    qDebug() << *dbtextfirst;
    query->prepare(*dbtextfirst);
    if(!query->exec())       qDebug() << "insert fail of deletefindstu";
    QSqlRecord rec = query->record();
    query->next();
    query->record();
    ui->lbdeletename        ->setText(                  query->value(rec.indexOf(  "stuname"      )).toString());
    ui->lbdeleteno          ->setText(                  query->value(rec.indexOf(  "stunumber"    )).toString());
    ui->lbdeleteclasslevel  ->setText(                  query->value(rec.indexOf(  "classlevel"   )).toString());
    ui->lbdeleteclassname   ->setText(                  query->value(rec.indexOf(  "classname"    )).toString());
    ui->lbdeletedepar       ->setText(                  query->value(rec.indexOf(  "department"   )).toString());
    ui->lbdeletecampus      ->setText(                  query->value(rec.indexOf(  "campus"       )).toString());
    ui->lbdeletesex         ->setText(g_CHSex[          query->value(rec.indexOf(  "sex"          )).toInt()  ]);
    ui->lbdeleteinstructor  ->setText(                  query->value(rec.indexOf(  "instructor"   )).toString());
    ui->lbdeletehteach      ->setText(                  query->value(rec.indexOf(  "headteacher"  )).toString());
    *dbtextfirst = "select * from test_db.dorm where stunameber = " + ui->ledeletestuno->text();
    query->prepare(*dbtextfirst);
    if(!query->exec())       qDebug() << "insert fail of deletefindstu";
    rec = query->record();
    query->next();
    query->record();
    ui->lbdeletebuilno      ->setText(g_CHBuildingno[   query->value(rec.indexOf(  "buildingno"   )).toInt  ()]);
    ui->lbdeletefloor       ->setText(g_CHFloor[        query->value(rec.indexOf(  "floor"        )).toInt  ()]);
    ui->lbdeletedormno      ->setText(                  query->value(rec.indexOf(  "dormitoryno"  )).toString());
    ui->lbdeletebedno       ->setText(                  query->value(rec.indexOf(  "bedno"        )).toString());

    delete(query);
    db.close();
}
//void MainWindow::slotscheckout()
//{
//    QString *stuno = new QString;
//    *stuno = ui->ledeletestuno->text();
//    checkout(stuno);
//}

