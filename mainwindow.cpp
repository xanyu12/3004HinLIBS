#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::getUI(){
    return ui;
}

void MainWindow::setControl(Control *c){
    controller = c;
}

void MainWindow::on_searchButton_clicked(){
    if(controller){
        controller->searchCatalogue();
    }
}
void MainWindow::on_catalogueTable_rowClicked(int row){
    if(!controller){
        return;
    }
    QString id = ui->CatalogueTable->item(row, 0)->text();
    string s = id.toStdString();
    QMessageBox::StandardButton reply;
    if(ui->checkOutMode->isChecked()){
        reply = QMessageBox::question(
                    this,
                    "Confirm Checkout",
                    "Are you sure you want to check out this item?",
                    QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes){
            controller->checkOutItem(s);
        }else{
            QMessageBox::information(this, "Cancelled", "Checkout Cancelled");
        }
    }else if(ui->placeHoldMode->isChecked()){
        reply = QMessageBox::question(
                    this,
                    "Confirm Hold",
                    "Are you sure you want to place a hold on this item?",
                    QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes){
            controller->placeHold(s);
        }else{
            QMessageBox::information(this, "Cancelled", "Hold Cancelled");
        }
    }
}

void MainWindow::on_adminButton_clicked()
{
    controller->handleAdminStart();
}

void MainWindow::on_patronButton_clicked()
{
    controller->handlePatronStart();
}


void MainWindow::on_staffButton_clicked()
{
    controller->handleLibrarianStart();
}


void MainWindow::on_libLoginButton_clicked()
{
    string username = ui->userInput->text().toStdString();
    string password = ui->passwordInput->text().toStdString();
    controller->handleLibrarianLogin(username, password);

}


void MainWindow::on_browseButton_clicked()
{
    controller->handlePatronBrowse();
}


void MainWindow::on_patronAccountButton_clicked()
{
    controller->handlePatronMyAccount();
}


