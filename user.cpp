#include "user.h"

User::User(string i, string n, string p, string c){
    userID = i;
    name = n;
    password = p;
    contact = c;
}

Patron::Patron(string i, string n, string p, string c, double b, bool s) : User(i, n, p, c), accountBalance(b), accountStatus(s){}

Patron::~Patron(){}
