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
    void setUser(User& u);

    void handleAdminStart();
    void handlePatronStart();
    void handleLibrarianStart();
    void handlePatronBrowse();
    void handlePatronMyAccount();


    void handlePatronLogin(string& cardNum, string& pin);
    void handleAdminLogin(string& username, string& password);
    void handleLibrarianLogin(string& username, string& password);
    void checkOutItem(string& s);
    void checkInItem(string& s);
    void placeHold(string& s);
    void cancelHold(string& s);
    void loadLibrary();

private:
    Boundary* ui;
    Library* library_;
    User* user;

};

#endif // CONTROL_H
