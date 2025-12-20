#ifndef WPLYWYDIALOG_H
#define WPLYWYDIALOG_H

#include <QDialog>
#include "budgetcontroller.h"

namespace Ui {
class WplywyDialog;
}

class WplywyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WplywyDialog(BudgetController *controller, QWidget *parent = nullptr);
    ~WplywyDialog();

private slots:
    void on_dodajWP_clicked();

private:
    Ui::WplywyDialog *ui;
    BudgetController *m_controller;
};

#endif
