#include "boundary.h"

/*
 * Function: Boundary object constructor
*/
Boundary::Boundary(Ui::MainWindow* m) : ui(m){}


/*
 * Function: Various page switching functions
*/
void Boundary::showStartPage(){
    ui->stackedWidget->setCurrentIndex(0);
}
void Boundary::showAdminLogin(){
    ui->stackedWidget->setCurrentIndex(2);
}
void Boundary::showPatronLogin(){
    ui->stackedWidget->setCurrentIndex(3);
}
void Boundary::showLibrarianLogin(){
    ui->stackedWidget->setCurrentIndex(1);
}
void Boundary::showPatronHomePage(){
    ui->stackedWidget->setCurrentIndex(4);
}
void Boundary::showPatronCataloguePage(){
    ui->stackedWidget->setCurrentIndex(5);
}
void Boundary::showPatronAccountPage(){
    ui->stackedWidget->setCurrentIndex(6);
}
void Boundary::showStaffHomePage(){
    ui->stackedWidget->setCurrentIndex(7);
}
void Boundary::showAdminHomePage(){
    ui->stackedWidget->setCurrentIndex(8);
}

void Boundary::showStaffAddPage(){
    ui->stackedWidget->setCurrentIndex(9);
}
void Boundary::showStaffRemovePage(){
    ui->stackedWidget->setCurrentIndex(10);
}
void Boundary::showStaffManagePage(){
    ui->stackedWidget->setCurrentIndex(11);
}

/*
 * Function: Various login error functions
*/
void Boundary::displayAdminLoginError(string& e){
    ui->adminErrorLabel->setText(QString::fromStdString(e));
}
void Boundary::displayPatronLoginError(string& e){
    ui->patronErrorLabel->setText(QString::fromStdString(e));
}
void Boundary::displayStaffLoginError(string& e){
    ui->staffErrorLabel->setText(QString::fromStdString(e));
}

/*
 * Function: Read search input
*/
string Boundary::getSearchInput()
{
    QString text = ui->hintonTitle->text();
    return text.toStdString();
}

/*
 * Function: Display library catalogue on QT table
 * In: Catalogue
*/
void Boundary::displayCatalogue(Library* lib){
    int size = lib->getCatalogueSize();
    cout << size << endl;
    ui->CatalogueTable->setRowCount(size);
    for(int i = 0; i < size; ++i){
        ui->CatalogueTable->setItem(i, 0, new QTableWidgetItem(lib->getItem(i, 1)));
        ui->CatalogueTable->setItem(i, 1, new QTableWidgetItem(lib->getItem(i, 2)));
        ui->CatalogueTable->setItem(i, 2, new QTableWidgetItem(lib->getItem(i, 6)));
        ui->CatalogueTable->setItem(i, 3, new QTableWidgetItem(lib->getItem(i, 7)));
    }
    ui->CatalogueTable->resizeColumnsToContents();
    ui->CatalogueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Boundary::displayCatalogueStaff(Library* lib){
    int size = lib->getCatalogueSize();
    cout << size << endl;
    ui->CatalogueTableStaffRemove->setRowCount(size);
    for(int i = 0; i < size; ++i){
        ui->CatalogueTableStaffRemove->setItem(i, 0, new QTableWidgetItem(lib->getItem(i, 1)));
        ui->CatalogueTableStaffRemove->setItem(i, 1, new QTableWidgetItem(lib->getItem(i, 2)));
        ui->CatalogueTableStaffRemove->setItem(i, 2, new QTableWidgetItem(lib->getItem(i, 6)));
        ui->CatalogueTableStaffRemove->setItem(i, 3, new QTableWidgetItem(lib->getItem(i, 7)));
    }
    ui->CatalogueTableStaffRemove->resizeColumnsToContents();
    ui->CatalogueTableStaffRemove->setSelectionBehavior(QAbstractItemView::SelectRows);
}

/*
 * Function: Display User Loans on QT table
 * In: Patron
*/
void Boundary::displayLoans(string& s, Library* lib){
    int size = lib->getNumLoans(s);
    ui->patronLoanTable->setRowCount(size);
    for(int i = 0; i < size; ++i){
        ui->patronLoanTable->setItem(i, 0, new QTableWidgetItem(lib->getLoanTitle(i, s)));
        ui->patronLoanTable->setItem(i, 1, new QTableWidgetItem(lib->getLoanDate(i, s)));
        ui->patronLoanTable->setItem(i, 2, new QTableWidgetItem(lib->getDaysLeft(i, s)));
    }
     ui->patronLoanTable->resizeColumnsToContents();
     ui->patronLoanTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}


/*
 * Function: Display User Loans on QT table
 * In: Patron
*/
void Boundary::displayLoansStaff(string& s, Library* lib){
    int size = lib->getNumLoans(s);
    cout << size <<  endl;
    ui->StaffUserLoanTable->setRowCount(size);
    for(int i = 0; i < size; ++i){
        ui->StaffUserLoanTable->setItem(i, 0, new QTableWidgetItem(lib->getLoanTitle(i, s)));
        ui->StaffUserLoanTable->setItem(i, 1, new QTableWidgetItem(lib->getLoanDate(i, s)));
        ui->StaffUserLoanTable->setItem(i, 2, new QTableWidgetItem(lib->getDaysLeft(i, s)));
    }
     ui->StaffUserLoanTable->resizeColumnsToContents();
     ui->StaffUserLoanTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

/*
 * Function: Display user holds on QT table
 * In: Patron
*/
void Boundary::displayHolds(string& s, Library* lib){
    int size = lib->getNumHolds(s);
    ui->patronHoldTable->setRowCount(size);
    for(int i = 0; i < size; ++i){
        ui->patronHoldTable->setItem(i, 0, new QTableWidgetItem(lib->getHoldTitle(i, s)));
        ui->patronHoldTable->setItem(i, 1, new QTableWidgetItem(lib->getHoldPos(i, s)));
    }
    ui->patronHoldTable->resizeColumnsToContents();
    ui->patronHoldTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

/*
 * Function: Display user account details
 * In: Patron
*/
void Boundary::displayAccount(Patron p){
    ui->patronNameText->setText(QString::fromStdString("Full Name: " + p.getName()));
    ui->patronBalanceText->setText(QString::fromStdString("Account Balance: $" + to_string(p.getAccountBalance())));
    ui->patronCardText->setText(QString::fromStdString("Library Card Number: " + p.getCardNum()));
    ui->patronContactText->setText(QString::fromStdString("Contact: " + p.getContact()));
    ui->patronStatusText->setText(QString::fromStdString("Status: " + p.getAccountStatus()));
    ui->patronUsernameText->setText(QString::fromStdString("Username: " + p.getUserID()));
}
