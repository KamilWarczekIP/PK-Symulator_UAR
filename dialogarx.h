#ifndef DIALOGARX_H
#define DIALOGARX_H

#include <QDialog>

namespace Ui {
class DialogArx;
}

class DialogArx : public QDialog
{
    Q_OBJECT

public:
    explicit DialogArx(QWidget *parent = nullptr);
    ~DialogArx();

private:
    Ui::DialogArx *ui;
};

#endif // DIALOGARX_H
