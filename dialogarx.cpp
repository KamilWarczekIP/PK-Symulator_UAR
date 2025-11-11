#include "dialogarx.h"
#include "ui_dialogarx.h"

DialogArx::DialogArx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogArx)
{
    ui->setupUi(this);
}

DialogArx::~DialogArx()
{
    delete ui;
}
