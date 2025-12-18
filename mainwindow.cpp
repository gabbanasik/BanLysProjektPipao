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


/*void MainWindow::on_analizaBtn_clicked()
{
    if (!m_analizaDialog) {
        // Tworzymy dialog Analizy, przekazując mu Kontroler
        m_analizaDialog = new AnalizaDialog(m_controller, this);
        m_analizaDialog->setWindowTitle("Analiza Budżetu");
        // AnalizaDialog jest podłączony do obu sygnałów w swoim konstruktorze
    }
    m_analizaDialog->show();
}
*/

void MainWindow::on_wplywyBtn_clicked()
{
    if (!m_wplywyDialog) {

        m_wplywyDialog = new WplywyDialog(m_controller, this);
        m_wplywyDialog->setWindowTitle("Dodawanie Wpływów");
        connect(m_controller, &BudgetController::influenceTotalChanged,
                m_wplywyDialog, &WplywyDialog::updateBalanceView);
        connect(m_controller, &BudgetController::expenseTotalChanged,
                m_wplywyDialog, &WplywyDialog::updateBalanceView);
    }
    m_wplywyDialog->exec();
    aktualizujBilans();
    m_wplywyDialog->updateBalanceView();
    m_wplywyDialog->show();

}


void MainWindow::on_wydatkiBtn_clicked()
{
    if (!m_wydatkiDialog) {
        m_wydatkiDialog = new WydatkiDialog(m_controller, this);
        m_wydatkiDialog->setWindowTitle("Dodawanie Wydatków");
        connect(m_controller, &BudgetController::expenseTotalChanged,
                m_wydatkiDialog, &WydatkiDialog::updateBalanceView);
        connect(m_controller, &BudgetController::influenceTotalChanged,
                m_wydatkiDialog, &WydatkiDialog::updateBalanceView);
    }

    m_wydatkiDialog->exec();
    aktualizujBilans();
    m_wydatkiDialog->updateBalanceView();
    m_wydatkiDialog->show();

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

