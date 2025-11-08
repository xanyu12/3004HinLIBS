#ifndef CONTROL_H
#define CONTROL_H

#include "defs.h"
#include "boundary.h"
#include "catalogue.h"
class Control
{
public:
    Control(Boundary* b, Catalogue* c);

    void runSystem();
    void searchCatalogue();
    void checkOutItem();
    void checkInItem();
    void populateCatalogue();

private:
    Boundary* ui;
    Catalogue* catalogue;

};

#endif // CONTROL_H
