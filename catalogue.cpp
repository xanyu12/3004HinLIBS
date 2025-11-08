#include "catalogue.h"

Catalogue::Catalogue()
{
    numItems = 0;
    catalogueID = "L0001";
}

Catalogue::~Catalogue(){}

void Catalogue::populate()
{
    FictionBook b1("B001", "", "", 0, "", "", "");
}
