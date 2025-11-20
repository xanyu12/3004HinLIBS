#ifndef LIBRARY_H
#define LIBRARY_H

#include "defs.h"
#include "catalogue.h"
#include "user.h"
#include <QtSql>

class Library
{
 public:
    Library();
    ~Library();

//    void populateUsers();
//    void addUser(Patron& p);
//    void addStaff(Librarian& l);
//    void addAdmin(Admin& a);
//    void loadCatalogue();

//    CatalogueItem* findItem(string& s);
//    Librarian* findStaffByName(string& s);
//    Admin* findAdminByName(string& s);
//    Patron* findUserByNum(string& n);
//    Patron* findUserByName(string & s);


    bool checkInItem(string& itemID, string& userID);
    bool checkOutItem(string& itemID, string& userID);
    bool createHold(string& itemID, string& userID);
    bool cancelHold(string& itemID, string& userID);

    double calculateFine(Date& d1, Date& d2);
    int getNumUsers();
    int getNumStaff();
    int getNumAdmin();

    Date getToday();
    Date convertFromString(string& s);

private:
    QSqlDatabase db;

    Catalogue collection;
    int numUsers;
    int numStaff;
    int numAdmin;
    Patron users[MAX_ARR];
    Librarian staff[MAX_ARR];
    Admin admin[MAX_ARR];

};

#endif // LIBRARY_H
