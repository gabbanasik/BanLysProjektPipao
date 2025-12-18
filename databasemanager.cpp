#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{

}

bool DatabaseManager::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    path.append("/moj_budzet.sqlite");

    db.setDatabaseName(path);
    if (!db.open()) {
        qDebug() << "Błąd! Nie można otworzyć bazy danych:" << db.lastError().text();
        return false;
    } else {
        qDebug() << "Sukces! Baza danych połączona. Plik:" << path;
        return createTables();
    }
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    QString wplywySql = "CREATE TABLE IF NOT EXISTS Wplywy ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "kwota REAL, "
                        "data DATE, "
                        "opis TEXT)";

    if (!query.exec(wplywySql)) {
        qDebug() << "Błąd tworzenia tabeli Wplywy:" << query.lastError().text();
        return false;
    }
    QString wydatkiSql = "CREATE TABLE IF NOT EXISTS Wydatki ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "kwota REAL, "
                         "kategoria TEXT, "
                         "data DATE, "
                         "opis TEXT)";

    if (!query.exec(wydatkiSql)) {
        qDebug() << "Błąd tworzenia tabeli Wydatki:" << query.lastError().text();
        return false;
    }

    return true;
}
