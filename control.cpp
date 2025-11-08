#include "control.h"

Control::Control(Boundary* b, Catalogue* c){
    ui = b;
    catalogue = c;
}

void Control::runSystem(){}


void Control::searchCatalogue()
{
    string s = ui->getSearchInput();
    catalogue->search(s);
}

void Control::checkOutItem(){
    CatalogueItem item = ui->getCatalogueItem();
    item.checkOut();
}
void Control::checkInItem(){
    CatalogueItem item = ui->getCatalogueItem();
    item.checkIn();
}
void Control::populateCatalogue(){

}
