#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "defs.h"
#include "ui_mainwindow.h"
#include "library.h"
#include <QObject>
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class Boundary : public QObject
{
    Q_OBJECT
public:
    Boundary(Ui::MainWindow* ui);

    string getSearchInput();
    void displayCatalogue(Library* l);
    void displayCatalogueStaff(Library* l);
    void displayLoans(string& s, Library* l);
    void displayLoansStaff(string& s, Library* l);
    void displayHolds(string& s, Library* l);
    void displayAccount(Patron p);

    void displayAdminLoginError(string& e);
    void displayStaffLoginError(string& e);
    void displayPatronLoginError(string& e);


    void showStartPage();
    void showAdminLogin();
    void showPatronLogin();
    void showLibrarianLogin();
    void showPatronHomePage();
    void showPatronCataloguePage();
    void showPatronAccountPage();
    void showStaffHomePage();
    void showStaffAddPage();
    void showStaffRemovePage();
    void showStaffManagePage();
    void showAdminHomePage();

private:
    Ui::MainWindow* ui;
};

#endif // BOUNDARY_H
