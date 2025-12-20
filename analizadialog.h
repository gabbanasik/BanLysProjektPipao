#ifndef ANALIZADIALOG_H
#define ANALIZADIALOG_H

#include <QDialog>
#include <QtCharts/QChartView>
#include "budgetcontroller.h"

// Użycie makra w nagłówku pozwala na używanie klas Charts w całym pliku

namespace Ui { class AnalizaDialog; }

class AnalizaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnalizaDialog(BudgetController *controller, QWidget *parent = nullptr);
    ~AnalizaDialog();

    // Publiczna metoda, aby MainWindow mogło ją wywołać po dodaniu wydatku
    void setupChart();

private:
    Ui::AnalizaDialog *ui;
    BudgetController *m_controller;

    // Funkcje pomocnicze
    QChartView* createPieChart(QString tytul, double wplywy, double wydatki);
    QChartView* createBarChart();
    QChartView* createLineChart();
};

#endif // ANALIZADIALOG_H
