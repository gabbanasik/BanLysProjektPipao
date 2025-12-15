#ifndef WPLYWYDIALOG_H
#define WPLYWYDIALOG_H

#include <QDialog>

namespace Ui {
class WplywyDialog;
}

class WplywyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WplywyDialog(QWidget *parent = nullptr);
    ~WplywyDialog();

private:
    Ui::WplywyDialog *ui;
};

#endif // WPLYWYDIALOG_H
