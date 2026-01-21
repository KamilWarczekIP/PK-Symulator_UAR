#ifndef ARXCOEFFICIENTITEM_HPP
#define ARXCOEFFICIENTITEM_HPP

#include <QWidget>

namespace Ui {
class arxCoefficientItem;
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
    Ui::arxCoefficientItem *ui;
};

#endif // ARXCOEFFICIENTITEM_HPP
