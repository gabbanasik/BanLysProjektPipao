#include "wydatkidialog.h"
#include "ui_wydatkidialog.h"
#include <QMessageBox>
#include <QDoubleValidator>

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
    QString text = ui->kwotaWY->text();
    bool ok;
    double amount = text.toDouble(&ok);

    if (!ok || amount <= 0.0) {
        if (!text.isEmpty()) {
            QMessageBox::warning(this, "Błąd", "Wprowadź poprawną kwotę większą od zera.");
        }
        return;
    }

    m_controller->addExpense(amount);

    ui->kwotaWY->clear();
    // ui->opisWY->clear(); // Wyczyść opis
}

// Slot aktualizujący Bilans Netto w prawym górnym rogu (caloscWY)
void WydatkiDialog::updateBalanceView()
{
    double totalInfluence = m_controller->getTotalInfluence();
    double totalExpense = m_controller->getTotalExpense();
    double balance = totalInfluence - totalExpense;

    QString balanceText = QString::number(balance, 'f', 2) + " zł";
    ui->caloscWY->setText(balanceText); // Używamy labela caloscWY


}
