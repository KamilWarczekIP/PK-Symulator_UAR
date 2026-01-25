#ifndef ARXCOEFFICIENTITEM_H
#define ARXCOEFFICIENTITEM_H

#include <QWidget>

namespace Ui {
class ArxCoefficientItem;
}

class arxCoefficientItem : public QWidget
{
    Q_OBJECT

public:
    explicit arxCoefficientItem(qint32 index, double A, double B, QWidget *parent = nullptr);
    ~arxCoefficientItem();
    double getA();
    double getB();

private slots:
    void on_doubleSpinBox_a_valueChanged(double arg1);

    void on_doubleSpinBox_b_valueChanged(double arg1);

    void on_horizontalSlider_b_valueChanged(int value);

    void on_horizontalSlider_a_valueChanged(int value);

private:
    Ui::ArxCoefficientItem *ui;
};

#endif // ARXCOEFFICIENTITEM_H
