#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "UAR.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void addToPlots(TickData tick_data);
private slots:
    void on_pushButton_symulacja_star_stop_released();


    void on_spinBox_symulacja_interwal_valueChanged(int arg1);

    void on_horizontalSlider_symulacja_interwal_valueChanged(int value);

    void on_spinBox_symulacja_interwal_editingFinished();

    void on_horizontalSlider_symulacja_interwal_sliderReleased();

private:
    Ui::MainWindow *ui;
    QChart* q_chart;
    QLineSeries* seria_wartosc_zadana;
    qreal temp = 0.01;

};

#endif // MAINWINDOW_H
