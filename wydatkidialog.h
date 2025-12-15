#ifndef WYDATKIDIALOG_H
#define WYDATKIDIALOG_H

#include <QDialog>

namespace Ui {
class WydatkiDialog;
}

class WydatkiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WydatkiDialog(QWidget *parent = nullptr);
    ~WydatkiDialog();

private:
    Ui::WydatkiDialog *ui;
};

#endif // WYDATKIDIALOG_H
