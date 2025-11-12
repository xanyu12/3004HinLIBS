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
void MainWindow::on_catalogueTable_rowClicked(int row, int col){
    if(!controller){
        return;
    }

    QString id = ui->CatalogueTable->item(row, 0)->text();
    controller->selectItem(id);
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
    QString username = ui->userInput->text();
    QString password = ui->passwordInput->text();
    controller->handleLibrarianLogin(username.toStdString(), password.toStdString());

}

