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
    FictionBook b2("FB00002", "Ring Shout", "P. Djeli Clark", 2020, Condition::New, "Hardcover", Status::Available, "9781250767028");
    FictionBook b3("FB00003", "The Mad Girls of New York", "Maya Rodale", 2022, Condition::Acceptable, "Paperback", Status::Available, "9780593436752");
    FictionBook b4("FB00004", "Sula", "Toni Morrison", 1973, Condition::New, "Paperback", Status::Available, "9781400033430");
    FictionBook b5("FB00005", "Jane Eyre", "Charlotte Bronte", 1847, Condition::Fine, "Paperback", Status::Available, "9780194614443");

    NonFictionBook b6("NB00001", "The Immortal Life of Henrietta Lacks", "Rebecca Skloot", 2010, Condition::New, "Hardcover", Status::Available, "9780230748699", "616.02");
    NonFictionBook b7("NB00002", "Wave", "Sonali Deraniyagala", 2013, Condition::New, "Paperback", Status::Available, "9781844089079", "954.93");
    NonFictionBook b8("NB00003", "The Warmth of Other Suns", "Isabel Wilkerson", 2010, Condition::New, "Hardcover", Status::Available, "9780679444329", "304.80");
    NonFictionBook b9("NB00004", "How to Survive a Plague", "David France", 2016, Condition::New, "Paperback", Status::Available, "9780307745439", "362.19");
    NonFictionBook b10("NB00005", "Guns, Germs, and Steel", "Jared Diamonhd", 1997, Condition::Acceptable, "Hardcover", Status::Available, "9780393061314", "303.42");

    Magazine m1("MA00001", "100th Anniversary Special", "Vogue", 1992, Condition::Acceptable, "Print", Status::Available, "19920401", Date(1, 4, 1992));
    Magazine m2("MA00002", "The Hot Spring of Yellowstone", "National Geogrpahic", 2009, Condition::Fine, "Print", Status::Available, "216-2", Date(1, 8, 2009));
    Magazine m3("MA00003", "Fast Break: NBA Superstar Jimmy Butler in California", "Architectural Digest", 2024, Condition::New, "Print", Status::Available, "20241101", Date(1, 11, 2024));

    Movie m4("MO00001", "Mickey 17", "Bong Joon Ho", 2025, Condition::New, "Blu-ray", Status::Available, "Sci-fi/Comedy", 10);
    Movie m5("MO00002", "Together", "Michael Shanks", 2025, Condition::New, "VHS Tape", Status::Available, "Horror", 7);
    Movie m6("MO00003", "Bones and All", "Luca Guadagnino", 2022, Condition::New, "DVD", Status::Available, "Horror/Romance", 8);

    VideoGame m7("VG00001", "The Witcher 3: Wild Hunt", "Andrzej Sapkowski", 2015, Condition::Fine, "PlayStation 4", Status::Available, "Action/Adventure", 10);
    VideoGame m8("VG00002", "Nintendogs", "Junji Morri", 2005, Condition::New, "Nintendo DS", Status::Available, "Pet-Raising Simulation", 9);
    VideoGame m9("VG00003", "Ratchett and Clank", "Brian Allgeier", 2002, Condition::Fine, "PlayStation 2", Status::Available, "Third-Person Shooter/Platformer", 8);
    VideoGame m10("VG00003", "Grand Theft Auto IV", "Leslie Benzies", 2008, Condition::Fine, "Windows", Status::Available, "Action/Adventure", 8);
}
