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

    Librarian* findStaffByName(string& s);
    Admin* findAdminByName(string& s);
    Patron* findUserByNum(string& n);
    Patron* findUserByName(string & s);

    string findStaff(string& s);
    string findAdmin(string& s);
    int findUser(string& n);

    bool checkInItem(string& itemID, string& userID);
    bool checkOutItem(string& itemID, string& userID);
    bool createHold(string& itemID, string& userID);
    bool cancelHold(string& itemID, string& userID);
    bool addItem(CatalogueItem* c, string& type);
    bool removeItem(string& itemID);

    Status translateToStatus(string& s);

    int getNumHolds(string& userID);
    int getNumLoans(string& userID);


    double calculateFine(Date& d1, Date& d2);
    int getNumUsers();
    int getNumStaff();
    int getNumAdmin();

    Date getToday();
    Date convertFromString(string& s);

    int getCatalogueSize();
    int getDaysLeft(int i, string& userID);
    QString getItem(int i, int j);
    QString getLoanTitle(int i, string& userID);
    QString getLoanDate(int i, string& userID);
    QString getHoldTitle(int i, string& userID);
    QString getHoldPos(int i, string& userID);



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
