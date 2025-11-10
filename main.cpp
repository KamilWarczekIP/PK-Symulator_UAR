#include "BUILD_DEFINE.h"

#ifdef MAIN

#include <QApplication>
#include "State.h"
#include "mainwindow.h"

int main(int argc, char **argv)
{
    State::getInstance();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
#endif
