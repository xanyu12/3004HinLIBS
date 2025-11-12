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
    loadLibrary();
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
    Patron p = user;
    ui->displayHolds(p);
    ui->showPatronAccountPage();
}

void Control::handleLibrarianLogin(string& username, string& password){
    cout << "Librarian Logging In" << endl;
    cout << "Name: " + username << endl;
    Librarian* u = library_->findStaffByName(username);
    string err = "";
    if(u){
         cout << "User Found" << endl;
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
    cout << "Admin Logging In" << endl;
    cout << "Name: " + username << endl;
    Admin* admin = library_->findAdminByName(username);
    string err = "";
    if(admin){
        cout << "User Found" << endl;
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
    cout << "Patron Logging In" << endl;
    cout << "Card: " + cardNum << endl;
    Patron* pat = library_->findUserByNum(cardNum);
    string err = "";
    if(pat){
         cout << "User Found" << endl;
        if(pat->getPin() == pin){
            ui->showPatronHomePage();
            setUser(*pat);
        }else{
            err = "Password Incorrect";
            ui->displayPatronLoginError(err);
        }
        err = "Username Incorrect";
        ui->displayPatronLoginError(err);
    }
}

void Control::handleLogout(){
    ui->showStartPage();
}
