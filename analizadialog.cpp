#include "analizadialog.h"
#include "ui_analizadialog.h"

AnalizaDialog::AnalizaDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AnalizaDialog)
{
    ui->setupUi(this);
}

AnalizaDialog::~AnalizaDialog()
{
    delete ui;
}
