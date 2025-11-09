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
    void loadCatalogue();
    void searchCatalogue(string& s);

private:
    Catalogue collection;
    User users[MAX_ARR];

};

#endif // LIBRARY_H
