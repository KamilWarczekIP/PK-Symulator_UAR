#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    q_chart = new QChart();
    q_chart->setTitle(tr("Testowy wykresik"));

    QLineSeries* series = new QLineSeries();
    for (int var = 0; var < 10; ++var) {
        series->append(var, qreal(var * var + rand()));
    }
    q_chart->addSeries(series);
    q_chart->createDefaultAxes();

    auto q_chart_view = new QChartView(q_chart, this->centralWidget());
    delete ui->graphicsView;
    ui->graphicsView = q_chart_view;
    ui->graphicsView->setGeometry(10, 10, 200, 180);
}

MainWindow::~MainWindow()
{
    delete q_chart;
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    static int a = 0;
    ui->graphicsView->move(10 + a, 100);
    a += 30;

}

