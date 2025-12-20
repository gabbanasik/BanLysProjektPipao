#include "analizadialog.h"
#include "ui_analizadialog.h"
#include <QVBoxLayout> // Potrzebne do układu wykresu
#include <QtSql/QSqlQuery>
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

QChartView* AnalizaDialog::createPieChart(QString tytul, double wplywy, double wydatki) {
    QPieSeries *series = new QPieSeries();
    series->append("Wpływy", wplywy);
    series->append("Wydatki", wydatki);

    if (series->count() > 1) {
        series->slices().at(0)->setBrush(Qt::green);
        series->slices().at(1)->setBrush(Qt::red);

        series->slices().at(0)->setLabel(QString("Wpływy: %1 zł").arg(wplywy));
        series->slices().at(1)->setLabel(QString("Wydatki: %1 zł").arg(wydatki));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tytul);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    return view;
}


void AnalizaDialog::setupChart() {
        QSqlQuery query;

        // 1. POBIERANIE DANYCH Z BAZY (Miesiąc i Kwartał)
        double mw = 0, me = 0, kw = 0, ke = 0;

        // Zapytania SQL (identyczne jak wcześniej)
        query.exec("SELECT SUM(kwota) FROM Wplywy WHERE strftime('%m', data) = strftime('%m', 'now')");
        if(query.next()) mw = query.value(0).toDouble();
        query.exec("SELECT SUM(kwota) FROM Wydatki WHERE strftime('%m', data) = strftime('%m', 'now')");
        if(query.next()) me = query.value(0).toDouble();

        query.exec("SELECT SUM(kwota) FROM Wplywy WHERE data >= date('now', '-3 month')");
        if(query.next()) kw = query.value(0).toDouble();
        query.exec("SELECT SUM(kwota) FROM Wydatki WHERE data >= date('now', '-3 month')");
        if(query.next()) ke = query.value(0).toDouble();

        // 2. CZYSZCZENIE STARYCH WYKRESÓW (To naprawia Twój problem!)
        auto wyczyscLayout = [](QWidget* widget) {
            if (widget->layout()) {
                QLayoutItem *item;
                while ((item = widget->layout()->takeAt(0)) != nullptr) {
                    if (item->widget()) delete item->widget();
                    delete item;
                }
            } else {
                new QVBoxLayout(widget);
            }
        };

        wyczyscLayout(ui->widgetMiesiac);
        wyczyscLayout(ui->widgetKwartal);

        auto vMiesiac = createPieChart("Ten miesiąc", mw, me);
        auto vKwartal = createPieChart("Ostatnie 3 miesiące", kw, ke);


        ui->widgetMiesiac->layout()->addWidget(vMiesiac);
        ui->widgetKwartal->layout()->addWidget(vKwartal);
    }

