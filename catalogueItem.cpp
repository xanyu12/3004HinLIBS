#include "catalogueItem.h"

/*
 * Function: Catalogue item constructors
*/
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

/*
 * Function: Catalogue item deconstructor
*/
CatalogueItem::~CatalogueItem(){
}

/*
 * Function: Various getters
*/
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

int CatalogueItem::getQueueSize(){
    return queueSize;
}
/*
 * Function: Translate book availability status from enum to string
 * In: enum Status
 * Out: string status
*/
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

/*
 * Function: Translate book condition status from enum to string
 * In: enum Condition
 * Out: string condition
*/
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


/*
 * Function: Check in item by Updating circulation status of item to available;
*/
void CatalogueItem::checkIn(){
    circulationStatus_ = Status::Available;
}

/*
 * Function: CHeck out item by updating circulation status of item to unavailable
*/
void CatalogueItem::checkOut(){
    circulationStatus_ = Status::Unavailable;

}

/*
 * Function: add a hold to the items hold queue
 * In: Hold to be added
*/
void CatalogueItem::addToQueue(Hold &h){
    if(queueSize < MAX_ARR){
        holdQueue[queueSize] = h;
        queueSize++;
    }else{
        cout << "Maximum Holds Reached" << endl;
    }
}

/*
 * Function: Remove a hold from the items hold queue;
 * In: string title of hold to be removed
*/
void CatalogueItem::removeFromQueue(string& h){
    int idx = -1;
    for(int i = 0; i < queueSize; ++i){
        if(holdQueue[i].getItemTitle() == h){
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
