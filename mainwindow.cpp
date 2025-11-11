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

    string id = ui->CatalogueTable->item(row, 0)->text();
    controller->selectItem(id);
}

void MainWindow::on_adminButton_clicked()
{
    controller->handleAdminStart();
}



