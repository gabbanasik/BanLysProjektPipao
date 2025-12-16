#include "wplywydialog.h"
#include "ui_wplywydialog.h"
#include <QMessageBox>
#include <QDoubleValidator>

WplywyDialog::WplywyDialog(BudgetController *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WplywyDialog),
    m_controller(controller)
{
    ui->setupUi(this);

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
    QString text = ui->kwotaWP->text();
    bool ok;
    double amount = text.toDouble(&ok);

    if (!ok || amount <= 0.0) {
        if (!text.isEmpty()) {
            QMessageBox::warning(this, "Błąd", "Wprowadź poprawną kwotę większą od zera.");
        }
        return;
    }

    m_controller->addInfluence(amount);

    ui->kwotaWP->clear();
    // ui->opisWP->clear(); // Wyczyść opis
}

// Slot aktualizujący Bilans Netto w prawym górnym rogu (caloscWP)
void WplywyDialog::updateBalanceView()
{
    double totalInfluence = m_controller->getTotalInfluence();
    double totalExpense = m_controller->getTotalExpense();
    double balance = totalInfluence - totalExpense;

    QString balanceText = QString::number(balance, 'f', 2) + " zł";
    ui->caloscWP->setText(balanceText); // Używamy labela caloscWP

}
