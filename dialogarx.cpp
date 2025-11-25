#include "dialogarx.h"
#include "ui_dialogarx.h"
#include <random>

DialogArx::DialogArx(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogArx)
{
    ui->setupUi(this);

    chart_zaklocenia = new QChart();
    seria_zaklocen = new QLineSeries();

    chart_zaklocenia->legend()->hide();

    ustaw_wykres();

    ui->zaklocenie_suwak->setValue(0);
    ui->zaklocenie_wartosc->setValue(0.0);

    aktualizuj_widok(0.0);
}

DialogArx::~DialogArx()
{
    delete ui;
}

void DialogArx::on_zaklocenie_suwak_valueChanged(int value)
{
    ui->zaklocenie_wartosc->setValue(value);
    aktualizuj_widok((double)value);
}

void DialogArx::on_zaklocenie_wartosc_valueChanged(int arg1)
{
    ui->zaklocenie_suwak->setValue(arg1);
    aktualizuj_widok((double)arg1);
}

void DialogArx::ustaw_wykres()
{
    chart_zaklocenia->addSeries(seria_zaklocen);

    //--- OŚ X ---
    auto *axisX = new QValueAxis();
    axisX->setRange(0, LICZBA_PROBEK - 1);
    axisX->setTitleText("Próbki");
    chart_zaklocenia->addAxis(axisX, Qt::AlignBottom);
    seria_zaklocen->attachAxis(axisX);

    //--- OŚ Y ---
    auto *axisY = new QValueAxis();
    axisY->setRange(-1.0, 1.0);
    axisY->setTitleText("Szum (znormalizowany)");
    chart_zaklocenia->addAxis(axisY, Qt::AlignLeft);
    seria_zaklocen->attachAxis(axisY);

    //--- CHART VIEW ---
    auto *chartView = new QChartView(chart_zaklocenia, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    // pełne rozciągnięcie
    chart_zaklocenia->setMargins(QMargins(0,0,0,0));
    chartView->setContentsMargins(0,0,0,0);

    chartView->setMinimumHeight(150);

    ui->chart_zaklocenia_view->addWidget(chartView);
}

//------------ GENERATOR SZUMU ------------
static double generuj_zaklocenia(double odchylenie)
{
    if (odchylenie <= 0.0)
        return 0.0;

    static std::mt19937 gen(std::random_device{}());
    std::normal_distribution<double> dist(0.0, odchylenie);
    return dist(gen);
}

void DialogArx::aktualizuj_widok(double odchylenie)
{
    seria_zaklocen->clear();

    for (int i = 0; i < LICZBA_PROBEK; i++)
    {
        double n = generuj_zaklocenia(odchylenie);

        double znorm;

        if (odchylenie == 0.0)
        {
            znorm = 0.0;   // prosta linia
        }
        else
        {
            znorm = n / (3.0 * odchylenie);

            if (znorm > 1.0) znorm = 1.0;
            if (znorm < -1.0) znorm = -1.0;
        }

        seria_zaklocen->append(i, znorm);
    }
}
