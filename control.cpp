#include "control.h"

Control::Control(Boundary* b, Library* l){
    ui = b;
    library_ = l;
}

void Control::selectCatalogueItem(string& s){
    Patron pat = ui->getPatron();
    CatalogueItem* item = library_->findItem(s);
    int mode = ui->getMode();
    if(mode == 0){
        library_->checkInItem(*item, pat);
    }else if((mode == 1)){
        library_->createHold(*item, pat);
    }
}

void Control::searchCatalogue(){
    string s = ui->getSearchInput();
    if(s.empty()){
        ui->displayError(s);
        return;
    }
    CatalogueItem* search = library_->findItem(s);
    ui->displaySearch(*search);
}


void Control::placeHold(){
    CatalogueItem item = ui->getCatalogueItem();
    Patron pat = ui->getPatron();
    library_->createHold(item, pat);
}

void Control::cancelHold(){
    CatalogueItem item = ui->getCatalogueItem();
    Patron pat = ui->getPatron();
    Hold h = ui->getHold();
    library_->cancelHold(item, pat, h);
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
    Librarian* user = library_->findStaffByName(username);
    string err = "";
    if(user){
        if(user->getPassword() == password){
            ui->showStaffHomePage();
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
            err = "Password Incorrect";
            ui->displayPatronLoginError(err);
        }
        err = "Username Incorrect";
        ui->displayPatronLoginError(err);
    }
}
