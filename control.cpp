#include "control.h"

Control::Control(Boundary* b, Library* l){
    ui = b;
    library_ = l;
}

void Control::setUser(User& u){
    user = &u;
}
void Control::checkOutItem(string &s){
    CatalogueItem* item = library_->findItem(s);
    library_->checkOutItem(*item, *user);
}

void Control::checkInItem(string &s){
    CatalogueItem* item = library_->findItem(s);
    library_->checkInItem(*item, *user);
}


void Control::placeHold(string& s){
    CatalogueItem* item = library_->findItem(s);
    library_->createHold(*item, *user);
}

void Control::cancelHold(string& s){
    CatalogueItem* item = library_->findItem(s);
    library_->cancelHold(*item, *user);
}

void Control::loadLibrary(){
    library_->loadCatalogue();
    library_->populateUsers();
}

void Control::runSystem(){
    ui->showStartPage();
}

void Control::handleAdminStart(){
    ui->showAdminLogin();
}

void Control::handlePatronStart(){
    ui->showPatronLogin();
}

void Control::handleLibrarianStart(){
    ui->showLibrarianLogin();
}

void Control::handlePatronBrowse(){
    ui->showPatronCataloguePage();
}

void Control::handlePatronMyAccount(){
    ui->showPatronAccountPage();
}

void Control::handleLibrarianLogin(string& username, string& password){
    Librarian* u = library_->findStaffByName(username);
    string err = "";
    if(u){
        if(u->getPassword() == password){
            ui->showStaffHomePage();
            setUser(*u);
        }else{
            err = "Password Incorrect";
            ui->displayStaffLoginError(err);
        }
        err = "Username Incorrect";
        ui->displayStaffLoginError(err);
    }
}

void Control::handleAdminLogin(string &username, string &password){
    Admin* admin = library_->findAdminByName(username);
    string err = "";
    if(admin){
        if(admin->getPassword() == password){
            ui->showAdminHomePage();
            setUser(*admin);
        }else{
            err = "Password Incorrect";
            ui->displayAdminLoginError(err);
        }
        err = "Username Incorrect";
        ui->displayAdminLoginError(err);
    }
}
void Control::handlePatronLogin(string &cardNum, string &pin){
    Patron* pat = library_->findUserByNum(cardNum);
    string err = "";
    if(pat){
        if(pat->getPin() == pin){
            ui->showStaffHomePage();
            setUser(*pat);
        }else{
            err = "Password Incorrect";
            ui->displayPatronLoginError(err);
        }
        err = "Username Incorrect";
        ui->displayPatronLoginError(err);
    }
}
