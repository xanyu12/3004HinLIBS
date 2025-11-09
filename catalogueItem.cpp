#include "catalogueItem.h"

CatalogueItem::CatalogueItem(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus)
    : itemID_(id), title_(title), creator_(creator), publicationYear_(publicationYear), condition_(condition), format_(format), circulationStatus_(circulationStatus){}

Book::Book(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string isbn)
    : CatalogueItem(id, title, creator, publicationYear, condition, format, circulationStatus), isbn_(isbn){}

FictionBook::FictionBook(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string isbn)
    : Book(id, title, creator, publicationYear, condition, format, circulationStatus, isbn){}

NonFictionBook::NonFictionBook(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string isbn, string deweyNum)
    : Book(id, title, creator, publicationYear, condition, format, circulationStatus, isbn), deweyNumber_(deweyNum){}

Magazine::Magazine(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string issueNum, Date publicationDate)
    : CatalogueItem(id, title, creator, publicationYear, condition, format, circulationStatus), issueNumber_(issueNum), publicationDate_(publicationDate){}

Movie::Movie(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string genre, int rating)
    : CatalogueItem(id, title, creator, publicationYear, condition, format, circulationStatus), genre_(genre), rating_(rating){}

VideoGame::VideoGame(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string genre, int rating)
    : CatalogueItem(id, title, creator, publicationYear, condition, format, circulationStatus), genre_(genre), rating_(rating){}

CatalogueItem::~CatalogueItem(){
}

string CatalogueItem::getID(){
    return itemID_;
}

string CatalogueItem::getTitle(){
    return title_;
}

string CatalogueItem::getCreator(){
    return creator_;
}

int CatalogueItem::getPublicationYear(){
    return publicationYear_;
}

Condition CatalogueItem::getCondition(){
    return condition_;
}

string CatalogueItem::getFormat(){
    return format_;
}

Status CatalogueItem::getCirculationStatus(){
    return circulationStatus_;
}
