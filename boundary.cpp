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

string Boundary::getSearchInput()
{
    QString text = ui->passwordInput->text();
    return text.toStdString();
}

//CatalogueItem Boundary::getCatalogueItem(){}
//Patron Boundary::getPatron(){}
//Hold Boundary::getHold(){}

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
    ui->CatalogueTable->resizeColumnToContents(0);
    ui->CatalogueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

//void Boundary::displayItem(CatalogueItem& i){}
//void Boundary::displayError(string& e){}
//void Boundary::displaySearch(CatalogueItem& i){}
//void Boundary::displayCheckOut(CatalogueItem& item){}
//void Boundary::displayCheckIn(CatalogueItem& item){}
