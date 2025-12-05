#include "control.h"

Control::Control(Boundary* b, Library* l){
    ui = b;
    library_ = l;
    currentUser = nullptr;
}

void Control::setUser(User* u){
    currentUser = u;
}

bool Control::addItem(CatalogueItem *c, string& type){
    cout << "ADDING " + c->getTitle() << endl;
    bool b = library_->addItem(c, type);
    if(b == true){
        cout << "ITEM ADDED" << endl;
        //clear spaces with boundary 3
        return true;
    }
    cout << "FAILED ADD" << endl;
    return false;
}

bool Control::removeItem(string &s){
    cout << "REMOVING " + s << endl;
    bool b  = library_->removeItem(s);
    if(b == true){
        cout << "ITEM REMOVED" << endl;
        ui->displayCatalogueStaff(library_);
        return true;
    }
    cout << "FAILED REMOVE" << endl;
    return false;
}

bool Control::checkOutItem(string &s){
    cout << "Checking Out: " + s << endl;
    string user = currentUser->getUserID();
    bool b = library_->checkOutItem(s, user);
    if(b == true){
        cout << "DONE CHECKOUT" << endl;
        ui->displayCatalogue(library_);
        return true;
    }
    cout << "FAILED CHECKOUT" << endl;
    return false;
}


bool Control::checkInItem(string &s){
    cout << "Checking In: " + s << endl;
    string user = currentUser->getUserID();
    bool b = library_->checkInItem(s, user);
    if(b == true){
        cout << "DONE CHECK IN" << endl;
        return true;
    }
    cout << "FAILED CHECK IN" << endl;
    return false;
}


bool Control::placeHold(string& s){
    cout << "Placing Hold: " + s << endl;
    string user = currentUser->getUserID();
    bool b = library_->createHold(s, user);
    if(b == true){
        return true;
    }
    return false;
}

bool Control::cancelHold(string& s){
    cout << "Cancelling Hold: " + s << endl;
    string user = currentUser->getUserID();
    bool b = library_->cancelHold(s, user);
    if(b == true){
        return true;
    }
    return false;
}

void Control::runSystem(){
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

void Control::handleLibrarianHome(){
    ui->showStaffHomePage();
}
void Control::handleLibrarianAdd(){
    ui->showStaffAddPage();
}
void Control::handleLibrarianRemove(){
    ui->displayCatalogueStaff(library_);
    ui->showStaffRemovePage();
}
void Control::handleLibrarianManage(){
    ui->showStaffManagePage();
}

void Control::handlePatronBrowse(){
    ui->displayCatalogue(library_);
    ui->showPatronCataloguePage();
}

void Control::handlePatronMyAccount(){
    string s = currentUser->getUserID();
    Patron* p = library_->findUserByName(s);
    cout << "Current User: " + p->getName() << endl;
    ui->displayHolds(s, library_);
    ui->displayLoans(s, library_);
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
    cout << pat->getPin() << endl;
    cout << pat->getName() << endl;
    if(pat){
         cout << "User Found" << endl;
        if(pat->getPin() == pin){
            ui->displayAccount(*pat);
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

void Control::userSearch(string& num){
    Patron *p = library_->findUserByNum(num);
    if(p){
        cout << "User Found" << endl;
        string s = p->getUserID();
        ui->displayLoansStaff(s, library_);
    }else{
        cout << "User Not Found" << endl;
    }
}

bool Control::checkInStaff(string &s, string& n){
    Patron *p = library_->findUserByNum(n);
    if(p){
        cout << "User Found" << endl;
        string u = p->getUserID();
        bool b = library_->checkInItem(s, u);
        if(b == true){
            cout << "DONE CHECK IN" << endl;
            return true;
        }
    }
    cout << "FAILED CHECK IN" << endl;
    return false;
}



