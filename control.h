#ifndef CONTROL_H
#define CONTROL_H

#include "defs.h"
#include "boundary.h"
#include "library.h"

class Control
{
public:
    Control(Boundary* b, Library* l);

    void runSystem();
    void setUser(User* u);

    void handleAdminStart();
    void handlePatronStart();
    void handleLibrarianStart();

    void handleLibrarianHome();
    void handleLibrarianAdd();
    void handleLibrarianRemove();
    void handleLibrarianManage();

    void handlePatronBrowse();
    void handlePatronMyAccount();
    void handlePatronHome();

    void handleLogout();
    void userSearch(string& user);


    void handlePatronLogin(string& cardNum, string& pin);
    void handleAdminLogin(string& username, string& password);
    void handleLibrarianLogin(string& username, string& password);
    bool checkOutItem(string& s);
    bool checkInItem(string& s);
    bool checkInStaff(string& s, string& n);
    bool placeHold(string& s);
    bool cancelHold(string& s);
    bool addItem(CatalogueItem* c, string& type);
    bool removeItem(string& s);
    void loadLibrary();

private:
    Boundary* ui;
    Library* library_;
    User* currentUser;

};

#endif // CONTROL_H
