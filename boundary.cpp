#include "boundary.h"

Boundary::Boundary(Ui::MainWindow* m) : ui(m){}

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
void Boundary::displayAdminLoginError(string& e){
    ui->adminErrorLabel->setText(QString::fromStdString(e));
}
void Boundary::displayPatronLoginError(string& e){
    ui->patronErrorLabel->setText(QString::fromStdString(e));
}
void Boundary::displayStaffLoginError(string& e){
    ui->staffErrorLabel->setText(QString::fromStdString(e));
}

string Boundary::getSearchInput()
{
    QString text = ui->hintonTitle->text();
    return text.toStdString();
}

void Boundary::displayCatalogue(Catalogue& c){
    ui->CatalogueTable->setRowCount(c.getNumItems());
    for(int i = 0; i < c.getNumItems(); ++i){
        CatalogueItem* curr = c.getItem(i);
        ui->CatalogueTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(curr->getTitle())));
        ui->CatalogueTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(curr->getCreator())));
        ui->CatalogueTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(curr->getFormat())));
        ui->CatalogueTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(curr->translateStatus(curr->getCirculationStatus()))));
    }
    ui->CatalogueTable->resizeColumnsToContents();
    ui->CatalogueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Boundary::displayLoans(Patron &p){
    cout << "Printing Loans" << endl;
    ui->patronLoanTable->setRowCount(p.getNumLoans());
    for(int i = 0; i < p.getNumLoans(); ++i){
        Loan* thisLoan = p.getLoanByIdx(i);
        CatalogueItem* curr = thisLoan->getItem();
        QDate today = QDate::currentDate();
        Date d(today.day(), today.month(), today.year());
        Date due = thisLoan->getLoanDate() + 14;
        ui->patronLoanTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(curr->getTitle())));
        ui->patronLoanTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(due.toString())));
        ui->patronLoanTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(to_string(due-d))));
    }
     ui->patronLoanTable->resizeColumnsToContents();
     ui->patronLoanTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Boundary::displayHolds(Patron &p){
    ui->patronHoldTable->setRowCount(p.getNumHolds());
    for(int i = 0; i < p.getNumHolds(); ++i){
        Hold* thisHold = p.getHoldByIdx(i);
        ui->patronHoldTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(thisHold->getItemTitle())));
        ui->patronHoldTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(to_string(thisHold->getPosition()))));
    }
    ui->patronHoldTable->resizeColumnsToContents();
    ui->patronHoldTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Boundary::displayAccount(Patron &p){
    ui->patronNameText->setText(QString::fromStdString("Full Name: " + p.getName()));
    ui->patronBalanceText->setText(QString::fromStdString("Account Balance: $" + to_string(p.getAccountBalance())));
    ui->patronCardText->setText(QString::fromStdString("Library Card Number: " + p.getCardNum()));
    ui->patronContactText->setText(QString::fromStdString("Contact: " + p.getContact()));
    ui->patronStatusText->setText(QString::fromStdString("Status: " + p.getAccountStatus()));
    ui->patronUsernameText->setText(QString::fromStdString("Username: " + p.getUserID()));
}
