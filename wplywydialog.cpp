#include "wplywydialog.h"
#include "ui_wplywydialog.h"
#include <QMessageBox>
#include <QDoubleValidator>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

WplywyDialog::WplywyDialog(BudgetController *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WplywyDialog),
    m_controller(controller)
{
    ui->setupUi(this);
ui->dodajWP->setStyleSheet("background-color: green; color: white; border-radius: 10px;");
    // Używamy prawidłowej nazwy z UI: dodajKwote
    connect(ui->dodajWP, &QPushButton::clicked, this, &WplywyDialog::on_dodajWP_clicked);

    // Walidator
    QDoubleValidator *validator = new QDoubleValidator(0.01, 9999999.00, 2, this);
    ui->kwotaWP->setValidator(validator);
}

WplywyDialog::~WplywyDialog()
{
    delete ui;
}

// Logika dodawania wpływu
void WplywyDialog::on_dodajWP_clicked()
{
    QString kwota = ui->kwotaWP->text();
    QString data = ui->dataWP->date().toString("yyyy-MM-dd");
    QString opis = ui->opisWP->text();
    bool ok;
    double amount = kwota.toDouble(&ok);

    if (!ok || amount <= 0.0) {
        if (!kwota.isEmpty()) {
            QMessageBox::warning(this, "Błąd", "Wprowadź poprawną kwotę większą od zera.");
        }
        return;
    }

    QSqlQuery query;
    // ZMIANA: Tabela Wplywy
    query.prepare("INSERT INTO Wplywy (kwota, data, opis) "
                  "VALUES (:kwota, :data, :opis)");

    query.bindValue(":kwota", kwota);
    query.bindValue(":data", data);
    query.bindValue(":opis", opis);

    if (query.exec()) {
        QMessageBox::information(this, "Sukces", "Wpływ został zapisany.");
        this->accept();
    } else {
        QMessageBox::critical(this, "Błąd Bazy", "Nie udało się zapisać:\n" + query.lastError().text());
    }

    m_controller->addInfluence(amount);

    ui->kwotaWP->clear();
    // ui->opisWP->clear(); // Wyczyść opis
}

