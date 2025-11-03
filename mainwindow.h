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

    void on_pushButton_dostosuj_parametry_clicked();

private:
    Ui::MainWindow *ui;

    QChart* chart_wartosc_zadana_i_regulowana;
    QChart* chart_uchyb;
    QChart* chart_sterowanie;
    QChart* chart_wszystko;


    QList<QPointF>* lista_wartosc_zadana;
    QList<QPointF>* lista_wartosc_regulowana;
    QList<QPointF>* lista_uchyb;
    QList<QPointF>* lista_sterowanie;
    qreal temp = 0.0;

};

#endif // MAINWINDOW_H
