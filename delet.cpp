#include "mainwindow.h"
#include "mainwindow.cpp"
void MainWindow::deletLineEdit()
{
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stuNmae->backspace();
    }
}
