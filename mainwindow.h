#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "budgetcontroller.h"
#include "wydatkidialog.h"
#include "wplywydialog.h"
#include"analizadialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_wplywyBtn_clicked();
    void on_wydatkiBtn_clicked();
    void on_analizaBtn_clicked();

private:
    Ui::MainWindow *ui;
    BudgetController *m_controller;
    WplywyDialog *m_wplywyDialog = nullptr;
    WydatkiDialog *m_wydatkiDialog = nullptr;
    AnalizaDialog *m_analizaDialog = nullptr;
    void aktualizujBilans();
};

#endif
