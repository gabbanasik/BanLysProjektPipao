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
    AnalizaDialog oknoAnalizy(this);
    oknoAnalizy.setModal(true);
    oknoAnalizy.exec();
}


void MainWindow::on_wplywyBtn_clicked()
{
    WplywyDialog oknoWplywow(this);
    oknoWplywow.setModal(true);
    oknoWplywow.exec();
}


void MainWindow::on_wydatkiBtn_clicked()
{
    WydatkiDialog oknoWydatkow(this);
    oknoWydatkow.setModal(true);
    oknoWydatkow.exec();
}

