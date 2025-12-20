#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wydatkidialog.h"
#include "wplywydialog.h"
#include "analizadialog.h"
#include <QtSql/QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_controller = new BudgetController(); // Zakładam, że masz kontroler
    aktualizujBilans();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Funkcja aktualizująca bilans na ekranie głównym
void MainWindow::aktualizujBilans() {
    QSqlQuery query;
    double wplywy = 0, wydatki = 0;

    query.exec("SELECT SUM(kwota) FROM Wplywy");
    if(query.next()) wplywy = query.value(0).toDouble();

    query.exec("SELECT SUM(kwota) FROM Wydatki");
    if(query.next()) wydatki = query.value(0).toDouble();

    double bilans = wplywy - wydatki;
    ui->labelBilans->setText(QString("%1 zł").arg(QString::number(bilans, 'f', 2)));
}

// Obsługa przycisku WYDATKI
void MainWindow::on_wydatkiBtn_clicked() {
    WydatkiDialog dialog(m_controller, this);

    if (dialog.exec() == QDialog::Accepted) {
        // 1. Odśwież bilans na głównym oknie
        aktualizujBilans();

        // 2. SZUKANIE OKNA ANALIZY I AKTUALIZACJA WYKRESÓW "W LOCIE"
        AnalizaDialog *otwartaAnaliza = this->findChild<AnalizaDialog*>();
        if (otwartaAnaliza) {
            otwartaAnaliza->setupChart();
        }
    }
}

// Obsługa przycisku WPŁYWY
void MainWindow::on_wplywyBtn_clicked() {
    WplywyDialog dialog(m_controller, this);

    if (dialog.exec() == QDialog::Accepted) {
        aktualizujBilans();

        AnalizaDialog *otwartaAnaliza = this->findChild<AnalizaDialog*>();
        if (otwartaAnaliza) {
            otwartaAnaliza->setupChart();
        }
    }
}

void MainWindow::on_analizaBtn_clicked() {
    AnalizaDialog *istniejaca = this->findChild<AnalizaDialog*>();

    if (istniejaca) {
        istniejaca->raise();           // Wyciągnij na wierzch
        istniejaca->activateWindow();  // Ustaw jako aktywne
    } else {
        // Stwórz nowe okno, ustaw MainWindow jako rodzica
        AnalizaDialog *analiza = new AnalizaDialog(m_controller, this);
        analiza->show();
    }
}
