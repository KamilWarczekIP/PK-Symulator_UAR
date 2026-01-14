#ifndef DIALOGARX_H
#define DIALOGARX_H

#include "State.h"
#include <QDialog>
#include <QtCharts>

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
        void zaczytaj_dane();
        void on_zaklocenie_suwak_valueChanged(int value);
        void on_zaklocenie_wartosc_valueChanged(int arg1);
        void on_opoznienie_suwak_valueChanged(int value);
        void on_opoznienie_wartosc_valueChanged(int arg1);
        void on_dodaj_wspolczynnik_clicked();
        void on_usun_wspolczynnik_clicked();
        void on_buttonBox_accepted();

    private:
        void ustaw_wykres();
        void aktualizuj_widok(double odchylenie);

        QChart *chart_zaklocenia = nullptr;
        QBarSeries *barSeries = nullptr;

        double odchylenie = 0.0;
        static constexpr int LICZBA_PROBEK = 5000;
        static constexpr double ILOSC_BINOW = 20;

        QBarCategoryAxis *axisX = nullptr;
        QValueAxis *axisY = nullptr;

        Ui::DialogArx *ui;
};


#endif // DIALOGARX_H
