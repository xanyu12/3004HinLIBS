#ifndef LIBRARY_H
#define LIBRARY_H

#include "defs.h"
#include "catalogue.h"
#include "user.h"

class Library
{
 public:
    Library();
    ~Library();

    void populateUsers();
    void addUser(User& u);
    void loadCatalogue();

    void searchCatalogue(string& s);
    void checkInItem(CatalogueItem& i);
    void checkOutItem(CatalogueItem& i);

    int getNumUsers();

private:
    Catalogue collection;
    User users[MAX_ARR];
    int numUsers;

};

#endif // LIBRARY_H
