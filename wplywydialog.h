#ifndef WPLYWYDIALOG_H
#define WPLYWYDIALOG_H

#include <QDialog>
#include "budgetcontroller.h" // Wymagane!

namespace Ui {
class WplywyDialog;
}

class WplywyDialog : public QDialog
{
    Q_OBJECT

public:
    // Konstruktor, który przyjmuje kontroler
    explicit WplywyDialog(BudgetController *controller, QWidget *parent = nullptr);
    ~WplywyDialog();

public slots:
    // Slot do aktualizacji labela w prawym górnym rogu
    void updateBalanceView();

private slots:
    // Slot dla przycisku DODAJ
    void on_dodajWP_clicked();

private:
    Ui::WplywyDialog *ui;
    BudgetController *m_controller;
};

#endif // WPLYWYDIALOG_H
