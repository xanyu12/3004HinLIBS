#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "defs.h"
#include "catalogueItem.h"

class Catalogue
{
public:
    Catalogue();
    ~Catalogue();

    void populate();
    CatalogueItem* search(string& s);
    CatalogueItem* getItem(int i);
    void addItem(CatalogueItem& i);

    int getNumItems();

private:
    string catalogueID;
    int numItems;
    CatalogueItem catalogueArr[MAX_ARR];
};

#endif // CATALOGUE_H
