#ifndef WYDATKIDIALOG_H
#define WYDATKIDIALOG_H

#include <QDialog>
#include "budgetcontroller.h" // Wymagane!

namespace Ui {
class WydatkiDialog;
}

class WydatkiDialog : public QDialog
{
    Q_OBJECT

public:
    // Konstruktor, który przyjmuje kontroler
    explicit WydatkiDialog(BudgetController *controller, QWidget *parent = nullptr);
    ~WydatkiDialog();

public slots:
    // Slot, który będzie wywoływany przez BudgetController (przez sygnał)
    void updateBalanceView();

private slots:
    // Slot dla przycisku DODAJ (dostosuj nazwę, jeśli to u Ciebie np. on_wydajWY_clicked)
    void on_dodajWY_clicked();

private:
    Ui::WydatkiDialog *ui;
    BudgetController *m_controller;
};

#endif // WYDATKIDIALOG_H
