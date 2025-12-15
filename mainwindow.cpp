#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analizadialog.h"
#include "wydatkidialog.h"
#include "wplywydialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_analizaBtn_clicked()
{
    this->hide();
    AnalizaDialog oknoAnalizy(this);
    oknoAnalizy.setModal(true);
    oknoAnalizy.exec();
    this->show();
}

//ala
void MainWindow::on_wplywyBtn_clicked()
{
    this->hide();
    WplywyDialog oknoWplywow(this);
    oknoWplywow.setModal(true);
    oknoWplywow.exec();
     this->show();
}


void MainWindow::on_wydatkiBtn_clicked()
{
    this->hide();
    WydatkiDialog oknoWydatkow(this);
    oknoWydatkow.setModal(true);
    oknoWydatkow.exec();
     this->show();
}

