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
    controller->selectCatalogueItem(s);
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


