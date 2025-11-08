#include "mainwindow.h"

#include <QApplication>

#include "control.h"

int main(int argc, char *argv[])
{
    Catalogue collection;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
