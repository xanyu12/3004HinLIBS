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
    int row = 1;
    for(int i = 0; i < c.getNumItems(); ++i){
        CatalogueItem* curr = c.getItem(i);
        ui->CatalogueTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(curr->getTitle())));
        ui->CatalogueTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(curr->getCreator())));
        ui->CatalogueTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(curr->getFormat())));
        ui->CatalogueTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(curr->translateStatus(curr->getCirculationStatus()))));
        ++row;
    }
    ui->CatalogueTable->resizeColumnsToContents();
    ui->CatalogueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Boundary::displayLoans(Patron &p){
    ui->patronLoanTable->setRowCount(p.getNumLoans());
    int row = 1;
    for(int i = 0; i < p.getNumLoans(); ++i){
        Loan* thisLoan = p.getLoanByIdx(i);
        CatalogueItem* curr = thisLoan->getItem();
        QDate today = QDate::currentDate();
        Date d(today.day(), today.month(), today.year());
        Date due = thisLoan->getLoanDate() + 14;
        ui->patronLoanTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(curr->getTitle())));
        ui->patronLoanTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(due.toString())));
        ui->patronLoanTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(to_string(due-d))));
    }
     ui->patronLoanTable->resizeColumnsToContents();
     ui->patronLoanTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Boundary::displayHolds(Patron &p){
    ui->patronHoldTable->setRowCount(p.getNumHolds());
    int row = 1;
    for(int i = 0; i < p.getNumHolds(); ++i){
        Hold* thisHold = p.getHoldByIdx(i);
        ui->patronHoldTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(thisHold->getItemTitle())));
        ui->patronHoldTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(to_string(thisHold->getPosition()))));
    }
    ui->patronHoldTable->resizeColumnsToContents();
    ui->patronHoldTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

