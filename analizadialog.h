#ifndef ANALIZADIALOG_H
#define ANALIZADIALOG_H

#include <QDialog>

namespace Ui {
class AnalizaDialog;
}

class AnalizaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnalizaDialog(QWidget *parent = nullptr);
    ~AnalizaDialog();



private:
    Ui::AnalizaDialog *ui;
};

#endif
