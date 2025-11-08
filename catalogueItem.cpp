#include "catalogueItem.h"

CatalogueItem::CatalogueItem(string i, string t, string c, int y, string co, string f, string ci) :itemID(i), title(t), creator(c), publicationYear(y), condition(co), format(f), circulationStatus(ci){}
Book::Book(string i, string t, string c, int y, string co, string f, string ci, string is) : CatalogueItem(i, t, c, y, co, f, ci), isbn(is){}
FictionBook::FictionBook(string i, string t, string c, int y, string co, string f, string ci, string is) : Book(i, t, c, y, co, f, ci, is){}

CatalogueItem::~CatalogueItem(){
}

string CatalogueItem::getID(){
    return itemID;
}

string CatalogueItem::getTitle(){
    return title;
}

string CatalogueItem::getCreator(){
    return creator;
}

int CatalogueItem::getPublicationYear(){
    return publicationYear;
}

string CatalogueItem::getCondition(){
    return condition;
}

string CatalogueItem::getFormat(){
    return format;
}

string CatalogueItem::getCirculationStatus(){
    return circulationStatus;
}
