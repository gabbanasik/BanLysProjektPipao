#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

class DatabaseManager
{
public:
    DatabaseManager();

    // Funkcja do nawiązywania połączenia
    bool connectToDatabase();

private:
    // Funkcja wewnętrzna do tworzenia tabel
    bool createTables();
};

#endif // DATABASEMANAGER_H
