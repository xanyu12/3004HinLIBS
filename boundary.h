#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "defs.h"
#include "user.h"
#include "catalogue.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class Boundary : public QObject
{
    Q_OBJECT
public:
    Boundary(Ui::MainWindow* ui);

    string getSearchInput();
    CatalogueItem getCatalogueItem();
    Patron getPatron();
    Hold getHold();

    void displayCatalogue(Catalogue& c);
    void displayItem(CatalogueItem& i);
    void displayError(string& e);
    void displaySearch(CatalogueItem& i);
    void displayCheckOut(CatalogueItem& item);
    void displayCheckIn(CatalogueItem& item);
private:
    Ui::MainWindow* ui;
};

#endif // BOUNDARY_H
