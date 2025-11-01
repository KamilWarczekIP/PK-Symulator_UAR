#include <iostream>
#include "State.h"
#include "mainwindow.h"
#include <QApplication>
#define MAIN2

#ifdef MAIN2
int main(int argc, char** argv)
{
    State::getInstance();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
#endif
