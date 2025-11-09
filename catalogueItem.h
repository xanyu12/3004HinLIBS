#ifndef CATALOGUEITEM_H
#define CATALOGUEITEM_H

#include "defs.h"
#include "hold.h"

class CatalogueItem
{
public:
    CatalogueItem(string id="", string title="", string creator="", int publicationYear=0, Condition condition=Condition::New, string format="", Status circulationStatus=Status::Available);
    virtual ~CatalogueItem();

    void checkOut();
    void checkIn();

    string getID();
    string getTitle();
    string getCreator();
    int getPublicationYear();
    Condition getCondition();
    string getFormat();
    Status getCirculationStatus();

private:
    string itemID_;
    string title_;
    string creator_;
    int publicationYear_;
    Condition condition_;
    string format_;
    Status circulationStatus_;
    Hold holdQueue[MAX_ARR];
};

class Book : public CatalogueItem {
public:
    Book(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string isbn);

    void getISBN();

private:
    string isbn_;
};

class FictionBook : public Book{
public:
    FictionBook(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string isbn);

};

class NonFictionBook : public Book{
public:
    NonFictionBook(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string isbn, string deweyNum);

    string getDeweyNumber();

private:
    string deweyNumber_;
};

class VideoGame : public CatalogueItem{
public:
    VideoGame(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string genre, int rating);

    string getGenre();
    int getRating();

private:
    string genre_;
    int rating_;

};

class Movie : public CatalogueItem{
public:
    Movie(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string genre, int rating);

    string getGenre();
    int getRating();

private:
    string genre_;
    int rating_;
};

class Magazine : public CatalogueItem{
public:
    Magazine(string id, string title, string creator, int publicationYear, Condition condition, string format, Status circulationStatus, string issueNum, Date publicationDate);

    int getIssueNumber();
    Date getPublicationDate();

private:
    string issueNumber_;
    Date publicationDate_;
};

#endif // CATALOGUEITEM_H
