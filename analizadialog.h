#ifndef ANALIZADIALOG_H
#define ANALIZADIALOG_H
#include"budgetcontroller.h"
#include <QDialog>
#include<QtCharts>

namespace Ui {
class AnalizaDialog;
}

class AnalizaDialog : public QDialog
{
    Q_OBJECT

public:
    // Konstruktor przyjmujący wskaźnik do kontrolera budżetu
    explicit AnalizaDialog(BudgetController *controller, QWidget *parent = nullptr);
    ~AnalizaDialog();

private:
    Ui::AnalizaDialog *ui;
    BudgetController *m_controller; // Nasz "mózg" z danymi

    // Elementy wykresu z modułu QtCharts
    QChart *m_chart;
    QChartView *m_viewMiesiac;
    QChartView *m_viewKwartal;
    QChartView* createBarChart();
    QChartView* createLineChart();
    // Metoda pomocnicza do budowania wykresu
    void setupChart();
    QChartView* createPieChart(QString tytul, double wplywy, double wydatki);
};
#endif
