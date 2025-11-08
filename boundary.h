#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "defs.h"
#include "patron.h"
#include "catalogue.h"

class Boundary
{
public:
    string getSearchInput();
    CatalogueItem getCatalogueItem();
    void displayCatalogue(Catalogue& c);
    void displayItem(CatalogueItem& i);
    void displayError(string& e);
    void displaySearch(CatalogueItem& i);
    void displayCheckOut(CatalogueItem& item);
    void displayCheckIn(CatalogueItem& item);
};






#endif // BOUNDARY_H
