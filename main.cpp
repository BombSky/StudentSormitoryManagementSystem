#include "mainwindow.h"

QSqlDatabase star_mysql();
void loginfun();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    loginfun();
    Dialog s;
    w.setWindowTitle("宿舍管理系统");
//    s.show();
    QObject::connect(&s,SIGNAL(showmain()),&w,SLOT(receivelogin()));
//    QApplication::addLibraryPath("./plugins");
    w.show();
    return a.exec();
}

void loginfun()
{

}
