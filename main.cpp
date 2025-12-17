#include "mainwindow.h"

#include <QApplication>
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Start aplikacji - test konsoli";
    DatabaseManager dbManager;
    if (dbManager.connectToDatabase()) {
        qDebug() << "Połączono z bazą w main!";
    } else {
        qDebug() << "Błąd połączenia w main!";
    }
    MainWindow w;
    w.show();
    return a.exec();
}
