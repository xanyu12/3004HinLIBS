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
    void selectItem(string& s);

    void handleAdminStart();
    void handlePatronStart();
    void handleLibrarianStart();
    void handlePatronLogin(string& cardNum, string& pin);
    void handleAdminLogin(string& username, string& password);
    void handleLibrarianLogin(string& username, string& password);
    void searchCatalogue();
    void checkOutItem();
    void checkInItem();
    void placeHold();
    void cancelHold();
    void loadLibrary();
    void getCurrentDate();


private:
    Boundary* ui;
    Library* library_;

};

#endif // CONTROL_H
