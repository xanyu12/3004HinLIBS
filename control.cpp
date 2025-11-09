#include "control.h"

Control::Control(Boundary* b, Library* l){
    ui = b;
    library_ = l;
}

void Control::searchCatalogue(){
    string s = ui->getSearchInput();
    library_->searchCatalogue(s);
}

void Control::checkOutItem(){
    CatalogueItem item = ui->getCatalogueItem();
    item.checkOut();
}

void Control::checkInItem(){
    CatalogueItem item = ui->getCatalogueItem();
    item.checkIn();
}

void Control::loadLibrary(){
    library_->loadCatalogue();
    library_->populateUsers();
}


void Control::runSystem(){}
