#ifndef DIALOGARX_H
#define DIALOGARX_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <qscatterseries.h>
#include <qvalueaxis.h>

namespace Ui {
class DialogArx;
}

class DialogArx : public QDialog
{
    Q_OBJECT

    public:
        explicit DialogArx(QWidget *parent = nullptr);
        ~DialogArx();

    private slots:
        //void onPreviewToggled(bool checked);
        void on_zaklocenie_suwak_valueChanged(int value);
        void on_zaklocenie_wartosc_valueChanged(int arg1);

    private:
        void ustaw_wykres();
        void aktualizuj_widok(double odchylenie);

        QChart *chart_zaklocenia = nullptr;
        QLineSeries *seria_zaklocen = nullptr;
        double odchylenie = 0.0;
        const int LICZBA_PROBEK = 200;
        QValueAxis *axisX = nullptr;
        QValueAxis *axisY = nullptr;


        Ui::DialogArx *ui;
};


#endif // DIALOGARX_H
