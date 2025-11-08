#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "defs.h"
#include "catalogueItem.h"

class Catalogue
{
public:
    Catalogue();
    ~Catalogue();

    void browse();
    void populate();
    void search(string& s);
    void addItem(CatalogueItem& i);
    void checkOutItem(string& itemId);
    void checkInItem(string& itemId);

    string getID();
    int getNumItems();

private:
    string catalogueID;
    int numItems;
    CatalogueItem collection[10];
};

#endif // CATALOGUE_H
