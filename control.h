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
    void searchCatalogue();
    void checkOutItem();
    void checkInItem();
    void loadLibrary();
    void getCurrentDate();

private:
    Boundary* ui;
    Library* library_;

};

#endif // CONTROL_H
