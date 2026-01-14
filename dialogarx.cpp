#include "dialogarx.h"
#include "ui_dialogarx.h"
#include <random>
#include <QtCharts/QBarCategoryAxis>


DialogArx::DialogArx(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogArx)
{
    ui->setupUi(this);

    chart_zaklocenia = new QChart();

    connect(ui->SliderA1, &QSlider::valueChanged, ui->SpinA1, &QDoubleSpinBox::setValue);
    connect(ui->SpinA1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->SliderA1, &QSlider::setValue);

    connect(ui->SliderA2, &QSlider::valueChanged, ui->SpinA2, &QDoubleSpinBox::setValue);
    connect(ui->SpinA2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->SliderA2, &QSlider::setValue);

    connect(ui->SliderA3, &QSlider::valueChanged, ui->SpinA3, &QDoubleSpinBox::setValue);
    connect(ui->SpinA3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->SliderA3, &QSlider::setValue);

    connect(ui->SliderB1, &QSlider::valueChanged, ui->SpinB1, &QDoubleSpinBox::setValue);
    connect(ui->SpinB1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->SliderB1, &QSlider::setValue);

    connect(ui->SliderB2, &QSlider::valueChanged, ui->SpinB2, &QDoubleSpinBox::setValue);
    connect(ui->SpinB2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->SliderB2, &QSlider::setValue);

    connect(ui->SliderB3, &QSlider::valueChanged, ui->SpinB3, &QDoubleSpinBox::setValue);
    connect(ui->SpinB3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), ui->SliderB3, &QSlider::setValue);

    barSeries = new QBarSeries(chart_zaklocenia);
    axisX = new QBarCategoryAxis(chart_zaklocenia);
    axisY = new QValueAxis(chart_zaklocenia);

    ustaw_wykres();

    zaczytaj_dane();
}


DialogArx::~DialogArx()
{
    delete ui;
}

void DialogArx::zaczytaj_dane()
{
    //Załaduj współczynniki
    std::vector<double> a = State().getARXCoefficientsA();
    std::vector<double> b = State().getARXCoefficientsB();

    a.resize(3, 0.0);
    b.resize(3, 0.0);

    ui->SpinA1->setValue(a[0]);
    ui->SpinA2->setValue(a[1]);
    ui->SpinA3->setValue(a[2]);

    ui->SpinB1->setValue(b[0]);
    ui->SpinB2->setValue(b[1]);
    ui->SpinB3->setValue(b[2]);

    ui->opoznienie_wartosc->setValue(State().getARXTransportDelay());

    ui->zaklocenie_wartosc->setValue(State().getARXNoiseStandardDeviation());

    ui->ograniczenie_wej_max->setValue(State().getARXInputLimits().second);
    ui->ograniczenie_wej_min->setValue(State().getARXInputLimits().first);

    ui->ograniczenie_wyj_max->setValue(State().getARXOutputLimits().second);
    ui->ograniczenie_wyj_min->setValue(State().getARXOutputLimits().first);
}

void DialogArx::on_opoznienie_suwak_valueChanged(int value)
{
    ui->opoznienie_wartosc->setValue(value);
}

void DialogArx::on_opoznienie_wartosc_valueChanged(int arg1)
{
    ui->opoznienie_suwak->setValue(arg1);
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
    chart_zaklocenia->removeAllSeries();

    barSeries = new QBarSeries(chart_zaklocenia);
    chart_zaklocenia->addSeries(barSeries);

    chart_zaklocenia->legend()->hide();

    // --- OŚ X: KATEGORIE ---
    axisX = new QBarCategoryAxis(chart_zaklocenia);
    chart_zaklocenia->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);
    QFont font;
    font.setPointSize(6);
    axisX->setLabelsFont(font);

    // --- OŚ Y: WARTOŚCI ---
    axisY = new QValueAxis(chart_zaklocenia);
    axisY->setRange(0, 1);
    chart_zaklocenia->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);
    axisY->setLabelsFont(font);

    auto *chartView = new QChartView(chart_zaklocenia, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    chart_zaklocenia->setMargins(QMargins(0,0,0,0));
    chart_zaklocenia->layout()->setContentsMargins(0,0,0,0);
    chartView->setContentsMargins(0,0,0,0);

    ui->chart_zaklocenia_view->addWidget(chartView);
}

//------------ GENERATOR SZUMU ------------
static double generuj_zaklocenia(double sigma)
{
    static std::mt19937 gen(std::random_device{}());
    std::normal_distribution<double> dist(0.0, sigma);
    return dist(gen);
}

void DialogArx::aktualizuj_widok(double sigma)
{
    barSeries->clear();
    axisX->clear();

    auto *set = new QBarSet("Zakłócenia");

    // ---------- PRZYPADEK sigma = 0 ----------
    if (sigma <= 0.0)
    {
        QStringList kategorie;
        for (int i = 0; i < ILOSC_BINOW; ++i)
        {
            *set << 0;
            kategorie << "";
        }

        barSeries->append(set);
        axisX->append(kategorie);
        axisY->setRange(0, 1);
        return;
    }

    // ---------- NORMALNY PRZYPADEK ----------
    const double minVal = -3.0 * sigma;
    const double maxVal =  3.0 * sigma;
    const double binWidth = (maxVal - minVal) / ILOSC_BINOW;

    QVector<int> histogram(ILOSC_BINOW, 0);

    // generowanie próbek
    for (int i = 0; i < LICZBA_PROBEK; ++i)
    {
        double val = generuj_zaklocenia(sigma);
        int bin = static_cast<int>((val - minVal) / binWidth);

        if (bin >= 0 && bin < ILOSC_BINOW)
            histogram[bin]++;
    }

    QStringList kategorie;
    int maxY = 0;

    for (int i = 0; i < ILOSC_BINOW; ++i)
    {
        *set << histogram[i];

        double from = minVal + i * binWidth;
        double to   = from + binWidth;

        kategorie << QString::number(from, 'f', 1);

        if (histogram[i] > maxY)
            maxY = histogram[i];
    }

    barSeries->append(set);
    axisX->append(kategorie);

    axisY->setRange(0, maxY * 1.1);
}

void DialogArx::on_dodaj_wspolczynnik_clicked()
{
    return;
}


void DialogArx::on_usun_wspolczynnik_clicked()
{
    return;
}


void DialogArx::on_buttonBox_accepted()
{
    std::vector<double> a(3), b(3);

    a[0] = ui->SpinA1->value();
    a[1] = ui->SpinA2->value();
    a[2] = ui->SpinA3->value();

    b[0] = ui->SpinB1->value();
    b[1] = ui->SpinB2->value();
    b[2] = ui->SpinB3->value();

    State().setARXCoefficients(a, b);
    State().setARXTransportDelay(ui->opoznienie_wartosc->value());
    State().setARXInputLimits(ui->ograniczenie_wej_min->value(), ui->ograniczenie_wej_max->value());
    State().setARXOutputLimits(ui->ograniczenie_wyj_min->value(), ui->ograniczenie_wyj_max->value());
    State().setARXNoiseStandardDeviation(ui->zaklocenie_wartosc->value());
}

