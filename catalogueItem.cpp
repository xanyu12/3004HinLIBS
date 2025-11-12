#include "catalogueItem.h"

CatalogueItem::CatalogueItem(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus)
    : itemID_(id), title_(title), creator_(creator), publicationYear_(publicationYear), condition_(condition), format_(format), circulationStatus_(circulationStatus), queueSize(0){}

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

string CatalogueItem::translateStatus(Status s){
    switch(s){
    case Status::Available:
        return "Available";
    case Status::Unavailable:
        return "Unavailable";
    case Status::Missing:
        return "Missing";
    case Status::Withdrawn:
        return "Withdrawn";
    }
}

string CatalogueItem::translateCondition(Condition c){
    switch(c){
    case Condition::Acceptable:
        return "Acceptable";
    case Condition::Fine:
        return "Fine";
    case Condition::New:
        return "New";
    case Condition::Poor:
        return "Poor";
    }
}


Status CatalogueItem::getCirculationStatus(){
    return circulationStatus_;
}

int CatalogueItem::getQueueSize(){
    return queueSize;
}

void CatalogueItem::checkIn(){
    circulationStatus_ = Status::Available;
}

void CatalogueItem::checkOut(){
    circulationStatus_ = Status::Unavailable;

}

void CatalogueItem::addToQueue(Hold &h){
    if(queueSize < MAX_ARR){
        holdQueue[queueSize] = h;
        queueSize++;
    }else{
        cout << "Maximum Holds Reached" << endl;
    }
}

void CatalogueItem::removeFromQueue(Hold &h){
    int idx = -1;
    for(int i = 0; i < queueSize; ++i){
        if(holdQueue[i].getHoldID() == h.getHoldID()){
            idx = i;
        }
    }

    if(idx != -1){
        for(int j = idx; j < queueSize - 1; ++j){
            holdQueue[j] = holdQueue[j+1];
            holdQueue[j].updatePosition();
        }
        queueSize--;
    }
}
