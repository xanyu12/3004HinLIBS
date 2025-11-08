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
    FictionBook b2("FB00002", "", "", 0, Condition::New, "", Status::Available, "");
    FictionBook b3("FB00003", "", "", 0, Condition::New, "", Status::Available, "");
    FictionBook b4("FB00004", "", "", 0, Condition::New, "", Status::Available, "");
    FictionBook b5("FB00005", "", "", 0, Condition::New, "", Status::Available, "");

    NonFictionBook b6("NB00001", "", "", 0, Condition::New, "", Status::Available, "", "");
    NonFictionBook b7("NB00002", "", "", 0, Condition::New, "", Status::Available, "", "");
    NonFictionBook b8("NB00003", "", "", 0, Condition::New, "", Status::Available, "", "");
    NonFictionBook b9("NB00004", "", "", 0, Condition::New, "", Status::Available, "", "");
    NonFictionBook b10("NB00005", "", "", 0, Condition::New, "", Status::Available, "", "");

    Magazine m1("MA00001", "", "", 0, Condition::New, "", Status::Available, 0, Date());
    Magazine m2("MA00002", "", "", 0, Condition::New, "", Status::Available, 0, Date());
    Magazine m3("MA00003", "", "", 0, Condition::New, "", Status::Available, 0, Date());

    Movie m4("MO00001", "", "", 0, Condition::New, "", Status::Available, "", 0);
    Movie m5("MO00002", "", "", 0, Condition::New, "", Status::Available, "", 0);
    Movie m6("MO00003", "", "", 0, Condition::New, "", Status::Available, "", 0);

    VideoGame m7("VG00001", "", "", 0, Condition::New, "", Status::Available, "", 0);
    VideoGame m8("VG00002", "", "", 0, Condition::New, "", Status::Available, "", 0);
    VideoGame m9("VG00003", "", "", 0, Condition::New, "", Status::Available, "", 0);
    VideoGame m10("VG00003", "", "", 0, Condition::New, "", Status::Available, "", 0);
}
