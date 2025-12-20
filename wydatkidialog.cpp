#include "wydatkidialog.h"
#include "ui_wydatkidialog.h"
#include <QMessageBox>
#include <QDoubleValidator>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

WydatkiDialog::WydatkiDialog(BudgetController *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WydatkiDialog),
    m_controller(controller)
{
    ui->setupUi(this);

    // Używamy nazwy z UI (np. dodajWY)
    connect(ui->dodajWY, &QPushButton::clicked, this, &WydatkiDialog::on_dodajWY_clicked);

    // Walidator
    QDoubleValidator *validator = new QDoubleValidator(0.01, 9999999.00, 2, this);
    ui->kwotaWY->setValidator(validator);
}

WydatkiDialog::~WydatkiDialog()
{
    delete ui;
}

// Logika dodawania wydatku
void WydatkiDialog::on_dodajWY_clicked()
{
    QString kwota = ui->kwotaWY->text();
    QString kategoria = ui->kategorieWY->currentText();
    QString data = ui->dataWY->date().toString("yyyy-MM-dd");
    QString opis = ui->opisWY->text();
    bool ok;
    double amount = kwota.toDouble(&ok);

    if (!ok || amount <= 0.0) {
        if (!kwota.isEmpty()) {
            QMessageBox::warning(this, "Błąd", "Wprowadź poprawną kwotę większą od zera.");
        }
        return;
    }

    //Przygotowanie zapytania SQL
    QSqlQuery query;
    // Używamy składni :nazwa_parametru, to bezpieczne podejście (chroni przed błędami SQL)
    query.prepare("INSERT INTO Wydatki (kwota, kategoria, data, opis) "
                  "VALUES (:kwota, :kategoria, :data, :opis)");

    // 3. Podstawienie wartości pod parametry
    query.bindValue(":kwota", kwota);
    query.bindValue(":kategoria", kategoria);
    query.bindValue(":data", data);
    query.bindValue(":opis", opis);

    // 4. Wykonanie zapytania
    if (query.exec()) {
        // Sukces
        QMessageBox::information(this, "Sukces", "Wydatek został zapisany.");
        this->accept(); // To zamyka okno i zwraca wynik 'QDialog::Accepted'
    } else {
        // Błąd
        QMessageBox::critical(this, "Błąd Bazy", "Nie udało się zapisać:\n" + query.lastError().text());
        qDebug() << "SQL Error:" << query.lastError().text();
    }

    m_controller->addExpense(amount);

    ui->kwotaWY->clear();
    // ui->opisWY->clear(); // Wyczyść opis
}


