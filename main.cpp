#include "mainwindow.h"

#include <QApplication>
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseManager dbManager;
    MainWindow w;
    w.show();
    return a.exec();
}
