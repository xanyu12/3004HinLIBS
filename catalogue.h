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
    CatalogueItem* search(string& s);
    void addItem(CatalogueItem& i);

    string getID();
    int getNumItems();

private:
    string catalogueID;
    int numItems;
    CatalogueItem catalogueArr[MAX_ARR];
};

#endif // CATALOGUE_H
