#ifndef WYDATKIDIALOG_H
#define WYDATKIDIALOG_H

#include <QDialog>
#include "budgetcontroller.h"
namespace Ui {
class WydatkiDialog;
}

class WydatkiDialog : public QDialog
{
    Q_OBJECT

public:

    explicit WydatkiDialog(BudgetController *controller, QWidget *parent = nullptr);
    ~WydatkiDialog();

public slots:
    void updateBalanceView();

private slots:

    void on_dodajWY_clicked();

private:
    Ui::WydatkiDialog *ui;
    BudgetController *m_controller;
};

#endif
