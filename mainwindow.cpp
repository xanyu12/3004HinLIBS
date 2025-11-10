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




