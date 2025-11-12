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
    void addUser(Patron& p);
    void addStaff(Librarian& l);
    void addAdmin(Admin& a);
    void loadCatalogue();

    CatalogueItem* findItem(string& s);
    Librarian* findStaffByName(string& s);
    Admin* findAdminByName(string& s);
    Patron* findUserByNum(string& n);

    void checkInItem(CatalogueItem& i, User& p);
    void checkOutItem(CatalogueItem& i, User& p);
    void createHold(CatalogueItem& i, User& p);
    void cancelHold(CatalogueItem& i, User& p);

    double calculateFine(Date& d1, Date& d2);

    int getNumUsers();
    int getNumStaff();
    int getNumAdmin();

    Date getToday();

private:
    Catalogue collection;
    int numUsers;
    int numStaff;
    int numAdmin;
    Patron users[MAX_ARR];
    Librarian staff[MAX_ARR];
    Admin admin[MAX_ARR];

};

#endif // LIBRARY_H
