#ifndef CONTROL_H
#define CONTROL_H

#include "defs.h"
#include "boundary.h"
#include "library.h"
#include "database.h"

class Control
{
public:
    Control(Boundary* b, Library* l, Database* db);

    void runSystem();
    void setUser(User* u);

    void handleAdminStart();
    void handlePatronStart();
    void handleLibrarianStart();
    void handlePatronBrowse();
    void handlePatronMyAccount();
    void handlePatronHome();
    void handleLogout();


    void handlePatronLogin(string& cardNum, string& pin);
    void handleAdminLogin(string& username, string& password);
    void handleLibrarianLogin(string& username, string& password);
    bool checkOutItem(string& s);
    bool checkInItem(string& s);
    bool placeHold(string& s);
    bool cancelHold(string& s);
    void loadLibrary();

private:
    Boundary* ui;
    Database* db;
    Library* library_;
    User* currentUser;

};

#endif // CONTROL_H
