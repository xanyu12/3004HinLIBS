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
    void checkInItem(CatalogueItem& i, Patron& p);
    void checkOutItem(CatalogueItem& i, Patron& p);

    double calculateFine(Date& d1, Date& d2);

    int getNumUsers();

private:
    Catalogue collection;
    User users[MAX_ARR];
    int numUsers;

};

#endif // LIBRARY_H
