#include "control.h"

Control::Control(Boundary* b, Library* l){
    ui = b;
    library_ = l;
}

void Control::searchCatalogue(){
    string s = ui->getSearchInput();
    if(s.empty()){
        ui->displayError("No Title Entered");
        return;
    }

    CatalogueItem* search = library_->searchCatalogue(s);
    ui->displaySearch(*search);
}

void Control::checkOutItem(){
    CatalogueItem item = ui->getCatalogueItem();
    Patron pat = ui->getPatron();
    library_->checkOutItem(item, pat);
}

void Control::checkInItem(){
    CatalogueItem item = ui->getCatalogueItem();
    Patron pat = ui->getPatron();
    library_->checkInItem(item, pat);
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

void Control::runSystem(){}
