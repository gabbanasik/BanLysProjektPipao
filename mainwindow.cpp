#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analizadialog.h"
#include "wydatkidialog.h"
#include "wplywydialog.h"
#include "budgetcontroller.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_controller = new BudgetController(this);
    aktualizujBilans();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_analizaBtn_clicked()
{
    if (!m_analizaDialog) {

    m_analizaDialog = new AnalizaDialog(m_controller, this);
    }
    m_analizaDialog->show();
}


void MainWindow::on_wplywyBtn_clicked()
{
    if (!m_wplywyDialog) {
        m_wplywyDialog = new WplywyDialog(m_controller, this);
        m_wplywyDialog->setWindowTitle("Dodawanie Wpływów");
        // USUNIĘTO: connect do updateBalanceView
    }

    m_wplywyDialog->exec(); // To otwiera okno i zatrzymuje kod tutaj do czasu jego zamknięcia
    aktualizujBilans();     // Wykona się natychmiast po zamknięciu okna wpływy
}

void MainWindow::on_wydatkiBtn_clicked()
{
    if (!m_wydatkiDialog) {
        m_wydatkiDialog = new WydatkiDialog(m_controller, this);
        m_wydatkiDialog->setWindowTitle("Dodawanie Wydatków");
        // USUNIĘTO: connect do updateBalanceView
    }

    m_wydatkiDialog->exec(); // To otwiera okno
    aktualizujBilans();      // Wykona się natychmiast po zamknięciu okna wydatki
}

void MainWindow::aktualizujBilans()
{
    QSqlQuery query;
    double sumaWplywow = 0.0;
    double sumaWydatkow = 0.0;
    if (query.exec("SELECT SUM(kwota) FROM Wplywy")) {
        if (query.next()) {
            sumaWplywow = query.value(0).toDouble();
        }
    }
    if (query.exec("SELECT SUM(kwota) FROM Wydatki")) {
        if (query.next()) {
            sumaWydatkow = query.value(0).toDouble();
        }
    }
    double bilans = sumaWplywow - sumaWydatkow;
    ui->labelBilans->setText(QString::number(bilans, 'f', 2) + " zł");

    if (bilans > 0) {
        ui->labelBilans->setStyleSheet("color: green; font-weight: bold;");
    } else if (bilans==0){
        ui->labelBilans->setStyleSheet("color: black; font-weight: bold;");
    }
    else{
         ui->labelBilans->setStyleSheet("color: red; font-weight: bold;");
    }
}

