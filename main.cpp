#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>

#include "control.h"
#include "database.h"

int main(int argc, char *argv[])
{
    Catalogue collection;


    QApplication a(argc, argv);
    QPushButton b;
    MainWindow w;

    Boundary boundary(w.getUI());
    Library library;
    Control controller(&boundary, &library);

    w.setControl(&controller);
    w.show();

    return a.exec();
}
