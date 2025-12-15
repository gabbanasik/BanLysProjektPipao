#include "wydatkidialog.h"
#include "ui_wydatkidialog.h"

WydatkiDialog::WydatkiDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WydatkiDialog)
{
    ui->setupUi(this);
}

WydatkiDialog::~WydatkiDialog()
{
    delete ui;
}
