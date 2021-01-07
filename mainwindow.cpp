#include "mainwindow.h"

//void bomb()
//{
//    QSqlDatabase db = star_mysql();
//    QSqlQuery *query  = new QSqlQuery;
//    QSqlQuery *queryforstulist = new QSqlQuery;
//    QString str1 = "SELECT * FROM test_db.stulist where stunumber = ";
//    str1 += "00000000002";
//    query->prepare(str1);
//    query->exec();
//    QSqlRecord rec = query->record();
//    QSqlRecord recforstulist = queryforstulist->record();



//    db.close();
//}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addNullItemForAddTableWidget();
    connect(ui->addButton,     &QPushButton::clicked, this, &MainWindow::switchPage     );
    connect(ui->deleteButton,  &QPushButton::clicked, this, &MainWindow::switchPage     );
    connect(ui->changeButton,  &QPushButton::clicked, this, &MainWindow::switchPage     );
    connect(ui->findButton,    &QPushButton::clicked, this, &MainWindow::switchPage     );
    connect(ui->addormPutIn,   &QPushButton::clicked, this, &MainWindow::setAddormPutIn );
    setMyLineEdit();        //设置输入框内容限制
    setFindTableViewHead();
    //点下提交收集学生信息
    connect(ui->addButtonPutIn   ,&QPushButton::clicked, this, &MainWindow::addPutIn       );
    //addorm
    connect(ui->addormFindBTN    ,&QPushButton::clicked, this, &MainWindow::addormFindList );
//    slots
    connect(ui->addormDelete     ,&QPushButton::clicked, this, &MainWindow::addormDelete   );
//    connect(ui->modifystu        ,&QPushButton::clicked, this, &MainWindow::modifyStu      );
    connect(ui->btndeletestu     ,&QPushButton::clicked, this, &MainWindow::deletestu      );
    connect(ui->btndeletefindstu ,&QPushButton::clicked, this, &MainWindow::deletefindstu  );
    connect(ui->pushButton_2     ,&QPushButton::clicked, this, &MainWindow::onlyleftout  );

    setAddTableWidget();
    setAddormWidget();
}

MainWindow::~MainWindow()   {   delete ui;  }

QSqlDatabase star_mysql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("sati");        //数据库名
    db.setUserName("root");                  //登陆身份
    db.setPassword("Bomb.sky");                //登陆密码
    if(!db.open())        qDebug() << "Failed" << endl;
    return db;
}

void MainWindow::switchPage(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());//得到按下的按钮的指针
    if(button==ui->addButton)
        ui->stack->setCurrentIndex(0);//根据按下的button按索引显示相应的页面
    else if(button==ui->findButton)
        ui->stack->setCurrentIndex(1);
    else if(button==ui->changeButton)
        ui->stack->setCurrentIndex(2);
    else if(button==ui->deleteButton)
        ui->stack->setCurrentIndex(3);
}

void MainWindow::checkout(QString *stuno)
{
    QSqlDatabase db = star_mysql();
    QSqlQuery *query  = new QSqlQuery;
    *stuno = "DELETE FROM test_db.dorm where stunameber = " + *stuno;
    query->prepare(*stuno);
    if(!query->exec())       qDebug() << "insert fail of deletestu.checkout";
    delete(query);
    db.close();

}

void MainWindow::receivelogin()
{
    this->show();
}



