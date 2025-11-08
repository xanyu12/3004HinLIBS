#include "catalogue.h"

Catalogue::Catalogue()
{
    numItems = 0;
    catalogueID = "L0001";
}

Catalogue::~Catalogue(){}

void Catalogue::populate()
{
    FictionBook b1("FB00001", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118");
    FictionBook b2("FB00002", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118");
    FictionBook b3("FB00003", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118");
    FictionBook b4("FB00004", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118");
    FictionBook b5("FB00005", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118");

    NonFictionBook b6("NB00001", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118", "");
    NonFictionBook b7("NB00002", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118", "");
    NonFictionBook b8("NB00003", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118", "");
    NonFictionBook b9("NB00004", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118", "");
    NonFictionBook b10("NB00005", "The Vegetarian", "Han Kang", 2007, Condition::New, "Paperback", Status::Available, "9781101906118", "");

}
