#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "State.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chart_sterowanie = new QChart();
    chart_sterowanie->setTitle(tr("Sterowanie (Wyjście z regulatora)"));
    chart_sterowanie->legend()->hide();

    chart_uchyb = new QChart();
    chart_uchyb->setTitle(tr("Uchyb"));
    chart_uchyb->legend()->hide();

    chart_wszystko = new QChart();
    chart_wszystko->setTitle(tr("Wszystko"));


    chart_wartosc_zadana_i_regulowana = new QChart();
    chart_wartosc_zadana_i_regulowana->setTitle(tr("Wartość zadana i regulowana"));
    chart_wartosc_zadana_i_regulowana->legend()->hide();

    lista_sterowanie = new QList<QPointF>();
    lista_uchyb = new QList<QPointF>();
    lista_wartosc_zadana = new QList<QPointF>();
    lista_wartosc_regulowana = new QList<QPointF>();



    chart_sterowanie->addSeries(new QScatterSeries());

    chart_uchyb->addSeries(new QScatterSeries());

    chart_wartosc_zadana_i_regulowana->addSeries(new QScatterSeries());
    chart_wartosc_zadana_i_regulowana->addSeries(new QScatterSeries());

    chart_wszystko->addSeries(new QScatterSeries());
    chart_wszystko->addSeries(new QScatterSeries());
    chart_wszystko->addSeries(new QScatterSeries());
    chart_wszystko->addSeries(new QScatterSeries());



    chart_sterowanie->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_sterowanie->axes(Qt::Horizontal).at(0)->setRange(0.0, 4.0);
    chart_sterowanie->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_sterowanie->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_uchyb->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_uchyb->axes(Qt::Horizontal).at(0)->setRange(0.0, 4.0);
    chart_uchyb->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_uchyb->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_wartosc_zadana_i_regulowana->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0)->setRange(0.0, 4.0);
    chart_wartosc_zadana_i_regulowana->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_wszystko->addAxis(new QValueAxis(), Qt::AlignBottom);
    chart_wszystko->axes(Qt::Horizontal).at(0)->setRange(0.0, 4.0);
    chart_wszystko->addAxis(new QValueAxis(), Qt::AlignLeft);
    chart_wszystko->axes(Qt::Vertical).at(0)->setRange(-5.0, 5.0);

    chart_sterowanie->series().at(0)->attachAxis(chart_sterowanie->axes(Qt::Horizontal).at(0));
    chart_sterowanie->series().at(0)->attachAxis(chart_sterowanie->axes(Qt::Vertical).at(0));

    chart_uchyb->series().at(0)->attachAxis(chart_uchyb->axes(Qt::Horizontal).at(0));
    chart_uchyb->series().at(0)->attachAxis(chart_uchyb->axes(Qt::Vertical).at(0));

    chart_wartosc_zadana_i_regulowana->series().at(0)->attachAxis(chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0));
    chart_wartosc_zadana_i_regulowana->series().at(0)->attachAxis(chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical).at(0));
    chart_wartosc_zadana_i_regulowana->series().at(1)->attachAxis(chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0));
    chart_wartosc_zadana_i_regulowana->series().at(1)->attachAxis(chart_wartosc_zadana_i_regulowana->axes(Qt::Vertical).at(0));

    chart_wszystko->series().at(0)->attachAxis(chart_wszystko->axes(Qt::Horizontal).at(0));
    chart_wszystko->series().at(0)->attachAxis(chart_wszystko->axes(Qt::Vertical).at(0));
    chart_wszystko->series().at(1)->attachAxis(chart_wszystko->axes(Qt::Horizontal).at(0));
    chart_wszystko->series().at(1)->attachAxis(chart_wszystko->axes(Qt::Vertical).at(0));
    chart_wszystko->series().at(2)->attachAxis(chart_wszystko->axes(Qt::Horizontal).at(0));
    chart_wszystko->series().at(2)->attachAxis(chart_wszystko->axes(Qt::Vertical).at(0));
    chart_wszystko->series().at(3)->attachAxis(chart_wszystko->axes(Qt::Horizontal).at(0));
    chart_wszystko->series().at(3)->attachAxis(chart_wszystko->axes(Qt::Vertical).at(0));

    auto q_chart_view = new QChartView(chart_sterowanie);
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);

    q_chart_view = new QChartView(chart_uchyb);
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);

    q_chart_view = new QChartView(chart_wartosc_zadana_i_regulowana);
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 2);

    q_chart_view = new QChartView(chart_wszystko);
    ui->verticalLayout_wykresy->addWidget(q_chart_view, 4);

    QObject::connect(&State::getInstance(), &State::sendTickDataToMainWindow, this, &MainWindow::addToPlots);
}
void MainWindow::addToPlots(TickData tick_data)
{
    qDebug() << tick_data.wartosc_regulowana;
    lista_wartosc_zadana->append(QPointF(temp += 0.1, tick_data.wartosc_zadana));
    lista_wartosc_regulowana->append(QPointF(temp, tick_data.wartosc_regulowana));
    lista_uchyb->append(QPointF(temp, tick_data.uchyb));
    lista_sterowanie->append(QPointF(temp, tick_data.sterowanie));

    dynamic_cast<QScatterSeries*>(chart_sterowanie->series().at(0))->replace(*lista_sterowanie);

    dynamic_cast<QScatterSeries*>(chart_uchyb->series().at(0))->replace(*lista_uchyb);

    dynamic_cast<QScatterSeries*>(chart_wartosc_zadana_i_regulowana->series().at(0))->replace(*lista_wartosc_zadana);
    dynamic_cast<QScatterSeries*>(chart_wartosc_zadana_i_regulowana->series().at(1))->replace(*lista_wartosc_regulowana);

    dynamic_cast<QScatterSeries*>(chart_wszystko->series().at(0))->replace(*lista_sterowanie);
    dynamic_cast<QScatterSeries*>(chart_wszystko->series().at(1))->replace(*lista_uchyb);
    dynamic_cast<QScatterSeries*>(chart_wszystko->series().at(2))->replace(*lista_wartosc_zadana);
    dynamic_cast<QScatterSeries*>(chart_wszystko->series().at(3))->replace(*lista_wartosc_regulowana);

    chart_sterowanie->axes(Qt::Horizontal).at(0)->setRange(temp - 40.0, temp+ 30*0.1);
    chart_uchyb->axes(Qt::Horizontal).at(0)->setRange(temp - 40.0, temp+ 30*0.1);
    chart_wartosc_zadana_i_regulowana->axes(Qt::Horizontal).at(0)->setRange(temp - 40.0, temp+ 30*0.1);
    chart_wszystko->axes(Qt::Horizontal).at(0)->setRange(temp - 40.0, temp+ 30*0.1);


    // if(seria_wartosc_zadana->points().count() > 40)
    // {
    //     seria_wartosc_zadana->removePoints(0, 1);
    //     seria_wartosc_regulowana->removePoints(0, 1);
    //     seria_uchyb->removePoints(0, 1);
    //     seria_sterowanie->removePoints(0, 1);
    // }


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


void MainWindow::on_pushButton_dostosuj_parametry_clicked()
{

}

