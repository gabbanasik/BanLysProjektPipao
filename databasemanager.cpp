#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{

}

bool DatabaseManager::connectToDatabase()
{
    // 1. Wybieramy sterownik bazy danych (SQLite)
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // 2. Ustalamy ścieżkę do pliku bazy danych
    // Używamy folderu Dokumenty użytkownika, żeby mieć prawa zapisu
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    path.append("/moj_budzet.sqlite");

    db.setDatabaseName(path);

    // 3. Próbujemy otworzyć bazę
    if (!db.open()) {
        qDebug() << "Błąd! Nie można otworzyć bazy danych:" << db.lastError().text();
        return false;
    } else {
        qDebug() << "Sukces! Baza danych połączona. Plik:" << path;
        return createTables(); // Jeśli połączono, stwórz tabele
    }
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;

    // --- TWORZENIE TABELI WPŁYWÓW ---
    // Pola: id (automat), data, kwota, kategoria, opis
    QString wplywySql = "CREATE TABLE IF NOT EXISTS Wplywy ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "kwota REAL, "
                        "data DATE, "
                        "opis TEXT)";

    if (!query.exec(wplywySql)) {
        qDebug() << "Błąd tworzenia tabeli Wplywy:" << query.lastError().text();
        return false;
    }

    // --- TWORZENIE TABELI WYDATKÓW ---
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
