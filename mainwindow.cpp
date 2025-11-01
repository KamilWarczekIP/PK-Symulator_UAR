#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "State.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    q_chart = new QChart();
    q_chart->setTitle(tr("Wartosc zadana"));

    seria_wartosc_zadana = new QLineSeries();
    q_chart->addSeries(seria_wartosc_zadana);
    q_chart->legend()->hide();

    auto axisX = new QValueAxis();
    axisX->setRange(0.0, 30.0);

    auto axisY = new QValueAxis();
    axisY->setRange(-5.0, 5.0);

    q_chart->addAxis(axisX, Qt::AlignBottom);
    q_chart->addAxis(axisY, Qt::AlignLeft);

    seria_wartosc_zadana->attachAxis(axisX);
    seria_wartosc_zadana->attachAxis(axisY);

    auto q_chart_view = new QChartView(q_chart);
    delete ui->graphicsView_wartosc_zadana_i_regulowana;
    ui->graphicsView_wartosc_zadana_i_regulowana = q_chart_view;
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 10);

    QObject::connect(&State::getInstance(), &State::sendTickDataToMainWindow, this, &MainWindow::addToPlots);
}
void MainWindow::addToPlots(TickData tick_data)
{
    qDebug() << "dziala :))" << tick_data.wartosc_zadana;
    seria_wartosc_zadana->append(temp += 0.01, tick_data.wartosc_zadana);


}
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_symulacja_star_stop_released()
{
    if(State::getInstance().getSymulacjaDziala())
    {
        State::getInstance().setSymulacjaDziala(false);
        ui->pushButton_symulacja_star_stop->setText(tr("START"));
    }
    else
    {
        State::getInstance().setSymulacjaDziala(true);
        ui->pushButton_symulacja_star_stop->setText(tr("STOP"));
    }

}





void MainWindow::on_spinBox_symulacja_interwal_valueChanged(int arg1)
{
    ui->horizontalSlider_symulacja_interwal->setValue(arg1);
}


void MainWindow::on_horizontalSlider_symulacja_interwal_valueChanged(int value)
{
    ui->spinBox_symulacja_interwal->setValue(value);
}



void MainWindow::on_spinBox_symulacja_interwal_editingFinished()
{
    State::getInstance().setInterwalSymulacjiMS(ui->spinBox_symulacja_interwal->value());
}


void MainWindow::on_horizontalSlider_symulacja_interwal_sliderReleased()
{
    State::getInstance().setInterwalSymulacjiMS(ui->horizontalSlider_symulacja_interwal->value());
}

