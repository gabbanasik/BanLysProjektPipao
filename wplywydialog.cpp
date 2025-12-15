#include "wplywydialog.h"
#include "ui_wplywydialog.h"

WplywyDialog::WplywyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WplywyDialog)
{
    ui->setupUi(this);
}

WplywyDialog::~WplywyDialog()
{
    delete ui;
}
