#ifndef DIALOGARX_H
#define DIALOGARX_H

#include "State.h"
#include "ARXCoefficientItem.hpp"
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
        void on_zaklocenie_wartosc_valueChanged(double arg1);
        void on_opoznienie_suwak_valueChanged(int value);
        void on_opoznienie_wartosc_valueChanged(int arg1);
        void on_dodaj_wspolczynnik_clicked();
        void on_usun_wspolczynnik_clicked();
        void on_buttonBox_accepted();

    private:
        void ustaw_wykres();
        void aktualizuj_widok(double odchylenie);
        static constexpr const int MAX_WSPOLCZYNNIKOW = 10;
        static constexpr const int MIN_WSPOLCZYNNIKOW = 3;
        void addAXRCoefficientItem(const double A, const double B);

        QChart *chart_zaklocenia;

        QLineSeries *rozklad_zaklocen;
        QValueAxis  *axisX;
        QValueAxis  *axisY;
        QWidget* arx_coefficients_widget;
        QVBoxLayout* arx_coefficients_layout;
        QVector<arxCoefficientItem*> arx_coefficients_items;

        const int LICZBA_PUNKTOW = 300;

        Ui::DialogArx *ui;
};


#endif // DIALOGARX_H
