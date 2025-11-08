#ifndef CATALOGUEITEM_H
#define CATALOGUEITEM_H

#include "defs.h"

class CatalogueItem
{
public:
    CatalogueItem(string i, string t, string c, int y, string co, string f, string ci);
    virtual ~CatalogueItem();

    void checkOut();
    void checkIn();
    void placeHold();
    void cancelHold();

    string getID();
    string getTitle();
    string getCreator();
    int getPublicationYear();
    string getCondition();
    string getFormat();
    string getCirculationStatus();

private:
    string itemID;
    string title;
    string creator;
    int publicationYear;
    string condition;
    string format;
    string circulationStatus;
};

class Book : public CatalogueItem {
public:
    Book(string i, string t, string c, int y, string co, string f, string ci, string is);

    void getISBN();

private:
    string isbn;
};

class FictionBook : public Book{
public:
    FictionBook(string i, string t, string c, int y, string co, string f, string ci, string is);
};

class NonFictionBook : public Book{
public:
    NonFictionBook(string i, string t, string c, int y, string co, string f, string ci, string is, string d);

    string getDeweyNumber();

private:
    string deweyNumber;
};

class VideoGame : public CatalogueItem{
public:
    VideoGame();

    string getGenre();
    int getRating();

private:
    string genre;
    int rating;

};

class Movie : public CatalogueItem{
public:
    Movie();

    string getGenre();
    int getRating();

private:
    string genre;
    int rating;
};

class Magazine : public CatalogueItem{
public:
    Magazine();

    int getIssueNumber();
    Date getPublicationDate();
private:
    int issueNumber;
    Date publicationDate;
};

#endif // CATALOGUEITEM_H
