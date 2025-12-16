#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analizadialog.h"
#include "wydatkidialog.h"
#include "wplywydialog.h"
#include "budgetcontroller.h" // Upewnij się, że ten nagłówek jest!

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inicjalizacja Kontrolera Danych
    m_controller = new BudgetController(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// -------------------------------------------------------------
// ANALIZA
// -------------------------------------------------------------

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
// -------------------------------------------------------------
// WPŁYWY (WplywyDialog)
// -------------------------------------------------------------

void MainWindow::on_wplywyBtn_clicked()
{
    if (!m_wplywyDialog) {
        // Tworzymy dialog Wpływów, przekazując mu Kontroler
        m_wplywyDialog = new WplywyDialog(m_controller, this);
        m_wplywyDialog->setWindowTitle("Dodawanie Wpływów");

        // KLUCZOWE: Podłączamy dialog do OBU sygnałów!
        connect(m_controller, &BudgetController::influenceTotalChanged,
                m_wplywyDialog, &WplywyDialog::updateBalanceView);
        connect(m_controller, &BudgetController::expenseTotalChanged,
                m_wplywyDialog, &WplywyDialog::updateBalanceView); // Reaguje na zmianę Wydatków!
    }

    // Ustawienie Bilansu początkowego przed pokazaniem
    m_wplywyDialog->updateBalanceView();

    m_wplywyDialog->show();
}

// -------------------------------------------------------------
// WYDATKI (WydatkiDialog)
// -------------------------------------------------------------

void MainWindow::on_wydatkiBtn_clicked()
{
    if (!m_wydatkiDialog) {
        // Tworzymy dialog Wydatków, przekazując mu Kontroler
        m_wydatkiDialog = new WydatkiDialog(m_controller, this);
        m_wydatkiDialog->setWindowTitle("Dodawanie Wydatków");

        // KLUCZOWE: Podłączamy dialog do OBU sygnałów!
        connect(m_controller, &BudgetController::expenseTotalChanged,
                m_wydatkiDialog, &WydatkiDialog::updateBalanceView);
        connect(m_controller, &BudgetController::influenceTotalChanged,
                m_wydatkiDialog, &WydatkiDialog::updateBalanceView); // Reaguje na zmianę Wpływów!
    }

    // Ustawienie Bilansu początkowego przed pokazaniem
    m_wydatkiDialog->updateBalanceView();

    m_wydatkiDialog->show();
}
