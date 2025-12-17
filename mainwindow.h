#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// Dodaj nagłówki dla klas
#include "budgetcontroller.h"
//#include "analizadialog.h"
#include "wydatkidialog.h"
#include "wplywydialog.h"

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
    // Zostawiamy nazwy z Twojego UI
  //  void on_analizaBtn_clicked();
    void on_wplywyBtn_clicked();
    void on_wydatkiBtn_clicked();

private:
    Ui::MainWindow *ui;
    // 1. Instancja Kontrolera Danych
    BudgetController *m_controller;

    // 2. Wskaźniki do Dialogów (aby były tworzone tylko raz)
   // AnalizaDialog *m_analizaDialog = nullptr;
    WplywyDialog *m_wplywyDialog = nullptr;
    WydatkiDialog *m_wydatkiDialog = nullptr;
    void aktualizujBilans();
};

#endif // MAINWINDOW_H
