#include "analizadialog.h"
#include "ui_analizadialog.h"
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

AnalizaDialog::AnalizaDialog(BudgetController *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalizaDialog),
    m_controller(controller)
{
    ui->setupUi(this);

    // KLUCZOWE: Usuń obiekt z pamięci po zamknięciu, aby można było go otworzyć ponownie
    setAttribute(Qt::WA_DeleteOnClose);

    setupChart();
}

AnalizaDialog::~AnalizaDialog()
{
    delete ui;
}

// Funkcja tworząca Wykres Kołowy
QChartView* AnalizaDialog::createPieChart(QString tytul, double wplywy, double wydatki) {
    QPieSeries *series = new QPieSeries();
    series->append(QString("Wpływy (%1 zł)").arg(wplywy), wplywy);
    series->append(QString("Wydatki (%1 zł)").arg(wydatki), wydatki);

    if (series->count() > 1) {
        series->slices().at(0)->setBrush(QColor("#27ae60"));
        series->slices().at(1)->setBrush(QColor("#e74c3c"));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tytul);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundVisible(false);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    return view;
}

// Funkcja tworząca Wykres Słupkowy
QChartView* AnalizaDialog::createBarChart() {
    QBarSet *set = new QBarSet("Kwota (zł)");
    QStringList categories;
    QSqlQuery query;

    query.exec("SELECT kategoria, SUM(kwota) FROM Wydatki GROUP BY kategoria ORDER BY SUM(kwota) DESC LIMIT 5");
    while(query.next()) {
        categories << query.value(0).toString();
        *set << query.value(1).toDouble();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);
    series->setLabelsVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Top 5 Kategorii Wydatków");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    return view;
}

// Funkcja tworząca Wykres Liniowy
QChartView* AnalizaDialog::createLineChart() {
    QLineSeries *series = new QLineSeries();
    QSqlQuery query;
    query.exec("SELECT data, SUM(kwota) FROM Wydatki WHERE data >= date('now', '-7 days') GROUP BY data ORDER BY data ASC");

    int i = 0;
    while(query.next()) {
        series->append(i++, query.value(1).toDouble());
    }

    series->setPointsVisible(true);
    series->setPointLabelsVisible(true);
    series->setPointLabelsFormat("@yPoint zł");

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Wydatki z ostatnich 7 dni");
    chart->createDefaultAxes();
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    return view;
}

// Główna funkcja odświeżająca
void AnalizaDialog::setupChart() {
    QSqlQuery query;
    double mw = 0, me = 0, kw = 0, ke = 0;

    query.exec("SELECT SUM(kwota) FROM Wplywy WHERE strftime('%m', data) = strftime('%m', 'now')");
    if(query.next()) mw = query.value(0).toDouble();
    query.exec("SELECT SUM(kwota) FROM Wydatki WHERE strftime('%m', data) = strftime('%m', 'now')");
    if(query.next()) me = query.value(0).toDouble();

    query.exec("SELECT SUM(kwota) FROM Wplywy WHERE data >= date('now', '-3 month')");
    if(query.next()) kw = query.value(0).toDouble();
    query.exec("SELECT SUM(kwota) FROM Wydatki WHERE data >= date('now', '-3 month')");
    if(query.next()) ke = query.value(0).toDouble();

    auto wyczyscLayout = [](QWidget* widget) {
        if (!widget->layout()) {
            new QVBoxLayout(widget);
        } else {
            QLayoutItem *item;
            while ((item = widget->layout()->takeAt(0)) != nullptr) {
                if (item->widget()) delete item->widget();
                delete item;
            }
        }
    };

    wyczyscLayout(ui->widgetMiesiac);
    wyczyscLayout(ui->widgetKwartal);
    wyczyscLayout(ui->widget);
    wyczyscLayout(ui->widget_2);

    ui->widgetMiesiac->layout()->addWidget(createPieChart("Bieżący Miesiąc", mw, me));
    ui->widgetKwartal->layout()->addWidget(createPieChart("Ostatnie 3 Miesiące", kw, ke));
    ui->widget->layout()->addWidget(createBarChart());
    ui->widget_2->layout()->addWidget(createLineChart());
}
