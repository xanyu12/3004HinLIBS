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
                "Confirm Hold Cancel",
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


void MainWindow::on_addItemButton_clicked()
{
    controller->handleLibrarianAdd();
}


void MainWindow::on_removeItemButton_clicked()
{
   controller->handleLibrarianRemove();
}


void MainWindow::on_managePatronButton_clicked()
{
    controller->handleLibrarianManage();
}


void MainWindow::on_staffBackFromAddButton_clicked()
{
    controller->handleLibrarianHome();
}


void MainWindow::on_staffLogoutFromAddButton_clicked()
{
    controller->handleLogout();
    ui->userInput->setText("");
    ui->passwordInput->setText("");
    ui->staffErrorLabel->setText("");

}


void MainWindow::on_staffBackFromRemoveButton_clicked()
{
    controller->handleLibrarianHome();

}


void MainWindow::on_staffLogoutFromRemoveButton_clicked()
{
    controller->handleLogout();
    ui->userInput->setText("");
    ui->passwordInput->setText("");
    ui->staffErrorLabel->setText("");

}

void MainWindow::on_staffBackFromManageButton_clicked()
{
    controller->handleLibrarianHome();
}


void MainWindow::on_staffLogoutFromManageButton_clicked()
{
    controller->handleLogout();
    ui->userInput->setText("");
    ui->passwordInput->setText("");
    ui->staffErrorLabel->setText("");
}



void MainWindow::on_staffPatronSearchButton_clicked()
{
    QString user = ui->staffPatronSearchInput->text();
    string u = user.toStdString();
    controller->userSearch(u);
}

void MainWindow::on_addButton_clicked()
{
    if(!controller){
        return;
    }
    CatalogueItem* c;
    string temp;

    QString id = ui->idInput->text();
    QString title = ui->titleInput->text();
    QString creator = ui->creatorInput->text();
    QString type = ui->typeInput->currentText();
    QString format = ui->formatInput->text();
    QString year = ui->yearInput->text();

    if(type == "Fiction Book" || type == "Non Fiction Book"){
        QString isbn = ui->isbnInput->text();
        if(type == "Non Fiction Book"){
            QString dewey = ui->deweyInput->text();
            c = new NonFictionBook(id.toStdString(), title.toStdString(), creator.toStdString(), year.toInt(), Condition::New, format.toStdString(), Status::Available, isbn.toStdString(), dewey.toStdString());
            temp = "BOOK";
        }else{
            c = new FictionBook(id.toStdString(), title.toStdString(), creator.toStdString(), year.toInt(), Condition::New, format.toStdString(), Status::Available, isbn.toStdString());
            temp = "BOOK";
        }
    }else if(type == "Movie" || type == "Video Game"){
        QString genre = ui->genreInput->text();
        QString rating = ui->ratingInput->text();
        if(type == "Movie"){
            c = new Movie(id.toStdString(), title.toStdString(), creator.toStdString(), year.toInt(), Condition::New, format.toStdString(), Status::Available, genre.toStdString(), rating.toInt());
            temp = "MOVIE";
        }else{
            c = new VideoGame(id.toStdString(), title.toStdString(), creator.toStdString(), year.toInt(), Condition::New, format.toStdString(), Status::Available, genre.toStdString(), rating.toInt());
            temp = "GAME";
        }
    }else if(type == "Magazine"){
        QString date = ui->dateInput->text();
        QString issue = ui->issueInput->text();
        c = new Magazine(id.toStdString(), title.toStdString(), creator.toStdString(), year.toInt(), Condition::New, format.toStdString(), Status::Available, issue.toStdString(), date.toStdString());
        temp = "MAGAZINE";
    }else{
        cout << "NOT ENOUGH INFO ERROR" << endl;
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
                this,
                "Confirm New Item",
                "Are you sure you want to add this item to the catalogue?",
                QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        bool a = controller->addItem(c, temp);
        if(a == true){
            QMessageBox::information(this, "ADD SUCCESSFUL", title + " has been added to the catalogue. Thank you!");
        }else{
            QMessageBox::warning(this, "ADD UNSUCCESSFUL", "We are unable to complete this action.");
        }
    }else{
        QMessageBox::information(this, "Cancelled", "Add Cancelled");

    }

}


void MainWindow::on_CatalogueTableStaffRemove_cellDoubleClicked(int row, int column)
{
    if(!controller){
        return;
    }
    QString id = ui->CatalogueTableStaffRemove->item(row, 0)->text();
    string s = id.toStdString();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
                this,
                "Confirm Removal",
                "Are you sure you want to remove this item?",
                QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        bool a = controller->removeItem(s);
        if(a == true){
            QMessageBox::information(this, "REMOVAL SUCCESSFUL", id + " has been removed from the catalogue. Thank you!");
        }else{
            QMessageBox::warning(this, "REMOVAL UNSUCCESSFUL", "We are unable to complete this action.");
        }
    }else{
        QMessageBox::information(this, "Cancelled", "Removal Cancelled");

    }
}


void MainWindow::on_StaffUserLoanTable_cellDoubleClicked(int row, int column)
{
    if(!controller){
        return;
    }
    QString id = ui->StaffUserLoanTable->item(row, 0)->text();
    string s = id.toStdString();
    QString user = ui->staffPatronSearchInput->text();
    string u = user.toStdString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
                this,
                "Confirm Checkin",
                "Are you sure you want to check in " + id + " for " + user + "?",
                QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        bool  a = controller->checkInStaff(s, u);
        if(a == true){
            QMessageBox::information(this, "CHECKIN SUCCESSFUL", id + " has been removed from users account. Thank you!");
        }else{
            QMessageBox::warning(this, "CHECKIN UNSUCCESSFUL", "We are unable to complete this action.");
        }
    }else{
        QMessageBox::information(this, "Cancelled", "Checkin Cancelled");

    }
}

