#include "control.h"

Control::Control(Boundary* b, Library* l){
    ui = b;
    library_ = l;
    currentUser = nullptr;
}

void Control::setUser(User* u){
    currentUser = u;
}
bool Control::checkOutItem(string &s){
    cout << "Checking Out: " + s << endl;
    CatalogueItem* item = library_->findItem(s);
    bool b = library_->checkOutItem(item, currentUser);
    if(b == true){
        cout << "DONE CHECKOUT" << endl;
        return true;
    }
    cout << "FAILED CHECKOUT" << endl;
    return false;
}

bool Control::checkInItem(string &s){
    cout << "Checking In: " + s << endl;
    CatalogueItem* item = library_->findItem(s);
    bool b = library_->checkInItem(item, currentUser);
    if(b == true){
        return true;
    }
    return false;
}


bool Control::placeHold(string& s){
    cout << "Placing Hold: " + s << endl;
    CatalogueItem* item = library_->findItem(s);
    bool b = library_->createHold(item, currentUser);
    if(b == true){
        return true;
    }
    return false;
}

bool Control::cancelHold(string& s){
    cout << "Cancelling Hold: " + s << endl;
    CatalogueItem* item = library_->findItem(s);
    bool b = library_->cancelHold(item, currentUser);
    if(b == true){
        return true;
    }
    return false;
}

void Control::loadLibrary(){
    library_->loadCatalogue();
    library_->populateUsers();
}

void Control::runSystem(){
    loadLibrary();
    ui->showStartPage();
}

void Control::handlePatronHome(){
    ui->showPatronHomePage();
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
    Catalogue p = library_->getCatalogue();
    ui->displayCatalogue(p);
    ui->showPatronCataloguePage();
}

void Control::handlePatronMyAccount(){
    string s = currentUser->getUserID();
    Patron* p = library_->findUserByName(s);
    ui->displayHolds(*p);
    ui->displayLoans(*p);
    ui->displayAccount(*p);
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
            setUser(u);
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
            setUser(admin);
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
            setUser(pat);
        }else{
            err = "Password Incorrect";
            ui->displayPatronLoginError(err);
        }
        err = "Username Incorrect";
        ui->displayPatronLoginError(err);
    }
}

void Control::handleLogout(){
    setUser(nullptr);
    ui->showStartPage();
}
