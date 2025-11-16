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
    c->runSystem();
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


void MainWindow::on_adminLoginButton_clicked()
{
    string username = ui->adminUserInput->text().toStdString();
    string password = ui->adminPasswordInput->text().toStdString();
    controller->handleAdminLogin(username, password);
}


void MainWindow::on_libLoginBackButton_clicked()
{
    controller->handleLogout();
    ui->userInput->setText("");
    ui->passwordInput->setText("");
    ui->staffErrorLabel->setText("");
}


void MainWindow::on_adminLoginBackButton_clicked()
{
    controller->handleLogout();
    ui->adminUserInput->setText("");
    ui->adminPasswordInput->setText("");
    ui->adminErrorLabel->setText("");
}


void MainWindow::on_patronBackButton_clicked()
{
    controller->handleLogout();
    ui->patronCardInput->setText("");
    ui->patronPinInput->setText("");
    ui->patronErrorLabel->setText("");
}


void MainWindow::on_patronLoginButton_clicked()
{
    string card = ui->patronCardInput->text().toStdString();
    string pin = ui->patronPinInput->text().toStdString();
    controller->handlePatronLogin(card, pin);
}


void MainWindow::on_patronLogoutFromHomeButton_clicked()
{
    controller->handleLogout();
    ui->patronCardInput->setText("");
    ui->patronPinInput->setText("");
    ui->patronErrorLabel->setText("");
}


void MainWindow::on_patronBackFromCatalogueButton_clicked()
{
    controller->handlePatronHome();
}


void MainWindow::on_patronLogoutFromCatalogueButton_clicked()
{
    controller->handleLogout();
    ui->patronCardInput->setText("");
    ui->patronPinInput->setText("");
    ui->patronErrorLabel->setText("");
}


void MainWindow::on_patronBackFromAccountButton_clicked()
{
     ui->patronHoldTable->clearContents();
     ui->patronLoanTable->clearContents();
    controller->handlePatronHome();
}


void MainWindow::on_patronLogoutFromAccountButton_clicked()
{
    controller->handleLogout();
    ui->patronCardInput->setText("");
    ui->patronPinInput->setText("");
}


void MainWindow::on_staffFromHomeLogoutButton_clicked()
{
    controller->handleLogout();
    ui->userInput->setText("");
    ui->passwordInput->setText("");
    ui->staffErrorLabel->setText("");
}


void MainWindow::on_adminFromHomeLogoutButton_clicked()
{
    controller->handleLogout();
    ui->adminUserInput->setText("");
    ui->adminPasswordInput->setText("");
    ui->adminErrorLabel->setText("");
}

void MainWindow::on_patronLoanTable_cellDoubleClicked(int row, int column)
{
    if(!controller){
        return;
    }
    QString id = ui->patronLoanTable->item(row, 0)->text();
    string s = id.toStdString();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
                this,
                "Confirm Checkout",
                "Are you sure you want to check in this item?",
                QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        controller->checkInItem(s);
        QMessageBox::information(this, "CHECKIN SUCCESSFUL", id + " has been removed from your account. Thank you!");
    }else{
        QMessageBox::information(this, "Cancelled", "Checkout Cancelled");

    }
}


void MainWindow::on_patronHoldTable_cellDoubleClicked(int row, int column)
{
    if(!controller){
        return;
    }
    QString id = ui->patronHoldTable->item(row, 0)->text();
    string s = id.toStdString();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
                this,
                "Confirm Checkout",
                "Are you sure you want to check in this item?",
                QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        controller->cancelHold(s);
        ui->patronHoldTable->item(row, 0)->setText("");
        ui->patronHoldTable->item(row, 1)->setText("");
        QMessageBox::information(this, "CANCEL HOLD SUCCESSFUL", id + " has been removed from your account.");

    }else{
        QMessageBox::information(this, "Cancelled", "Checkout Cancelled");

    }
 }


void MainWindow::on_CatalogueTable_cellDoubleClicked(int row, int column)
{
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
            bool a  = controller->checkOutItem(s);
            if(a == true){
                QMessageBox::information(this, "CHECKOUT SUCCESSFUL", id + " has been added to your account. You have 14 days. Enjoy!");
            }else{
                QMessageBox::warning(this, "CHECKOUT UNSUCCESSFUL", "We are unable to complete this action as you either have reached max loans, have a locked account or the item is not available. You may place a hold instead!");
            }

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
            bool a = controller->placeHold(s);
            if(a == true){
                QMessageBox::information(this, "HOLD SUCCESSFUL", id + " has been added to your account. Check your queue position on My Account. Enjoy!");
            }else{
                QMessageBox::warning(this, "HOLD UNSUCCESSFUL", "We are unable to complete this action as this item is available. You may checkout instead!");
            }
        }else{
            QMessageBox::information(this, "Cancelled", "Hold Cancelled");
        }
    }
}

