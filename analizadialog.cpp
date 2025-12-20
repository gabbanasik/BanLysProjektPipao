#include "analizadialog.h"
#include "ui_analizadialog.h"
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

AnalizaDialog::AnalizaDialog(BudgetController *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalizaDialog),
    m_controller(controller)
{
    ui->setupUi(this);
    setupChart();
}

AnalizaDialog::~AnalizaDialog()
{
    delete ui;
}

// 1. WYKRES KOŁOWY (Już masz - Miesiąc i Kwartał)
    QChartView* AnalizaDialog::createPieChart(QString tytul, double wplywy, double wydatki) {
    QPieSeries *series = new QPieSeries();

    // Dodajemy dane - nazwy w append() trafią automatycznie do Legendy
    // Dodajemy kwoty do nazw, aby legenda była od razu informacyjna
    series->append(QString("Wpływy (%1 zł)").arg(wplywy), wplywy);
    series->append(QString("Wydatki (%1 zł)").arg(wydatki), wydatki);

    // Ustawiamy kolory bezpośrednio na plastrach
    if (series->count() > 0) {
        series->slices().at(0)->setBrush(QColor("#27ae60")); // Zielony
        if (series->count() > 1) {
            series->slices().at(1)->setBrush(QColor("#e74c3c")); // Czerwony
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tytul);

    // Animacje sprawiają, że wykres wygląda nowocześnie bez etykiet
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Konfiguracja Legendy - tutaj będą wyświetlone kwoty
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Arial", 10));

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

    // Opcjonalnie: Ustawienie tła na przezroczyste, by pasowało do okna
    chart->setBackgroundVisible(false);

    return view;
}
// 2. WYKRES SŁUPKOWY (Kategorie wydatków) - dla ui->widget
QChartView* AnalizaDialog::createBarChart() {
    QBarSet *set = new QBarSet("Kwota zł");
    QStringList categories;
    QSqlQuery query;

    query.exec("SELECT kategoria, SUM(kwota) FROM Wydatki GROUP BY kategoria LIMIT 5");
    while(query.next()) {
        categories << query.value(0).toString();
        *set << query.value(1).toDouble();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    // KLUCZ: Wyświetlanie liczb nad słupkami
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);

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

// 3. WYKRES LINIOWY (Historia wydatków) - dla ui->widget2
QChartView* AnalizaDialog::createLineChart() {
    QLineSeries *series = new QLineSeries();

    QSqlQuery query;
    query.exec("SELECT data, SUM(kwota) FROM Wydatki WHERE data >= date('now', '-7 days') GROUP BY data ORDER BY data ASC");

    int i = 0;
    while(query.next()) {
        series->append(i++, query.value(1).toDouble());
    }

    // Dodanie kropek na załamaniach linii
    series->setPointsVisible(true);
    series->setPointLabelsVisible(true); // Wyświetli kwotę przy kropce
    series->setPointLabelsFormat("@yPoint zł"); // Format wyświetlania ceny

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Wydatki w ostatnim tygodniu");
    chart->createDefaultAxes();

    // Stylizacja osi dla lepszej czytelności
    chart->axes(Qt::Vertical).first()->setTitleText("Kwota (zł)");
    chart->axes(Qt::Horizontal).first()->setTitleText("Dni");

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    return view;
}

void AnalizaDialog::setupChart() {
    QSqlQuery query;

    // Pobieranie danych dla PieChartów
    double mw = 0, me = 0, kw = 0, ke = 0;
    query.exec("SELECT SUM(kwota) FROM Wplywy WHERE strftime('%m', data) = strftime('%m', 'now')");
    if(query.next()) mw = query.value(0).toDouble();
    query.exec("SELECT SUM(kwota) FROM Wydatki WHERE strftime('%m', data) = strftime('%m', 'now')");
    if(query.next()) me = query.value(0).toDouble();

    query.exec("SELECT SUM(kwota) FROM Wplywy WHERE data >= date('now', '-3 month')");
    if(query.next()) kw = query.value(0).toDouble();
    query.exec("SELECT SUM(kwota) FROM Wydatki WHERE data >= date('now', '-3 month')");
    if(query.next()) ke = query.value(0).toDouble();

    // Funkcja czyszcząca layouty
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

    // Czyszczenie wszystkich 4 widgetów
    wyczyscLayout(ui->widgetMiesiac);
    wyczyscLayout(ui->widgetKwartal);
    wyczyscLayout(ui->widget);
    wyczyscLayout(ui->widget_2);

    // Generowanie wykresów
    auto vMiesiac = createPieChart("Wpływy vs Wydatki (Miesiąc)", mw, me);
    auto vKwartal = createPieChart("Wpływy vs Wydatki (Kwartał)", kw, ke);
    auto vBar = createBarChart();
    auto vLine = createLineChart();

    // Dodawanie do UI
    ui->widgetMiesiac->layout()->addWidget(vMiesiac);
    ui->widgetKwartal->layout()->addWidget(vKwartal);
    ui->widget->layout()->addWidget(vBar);
    ui->widget_2->layout()->addWidget(vLine);
}
