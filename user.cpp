#include "user.h"

User::User(string i, string n, string c){
    userID = i;
    name = n;
    contact = c;
}

Patron::Patron(string i, string n, string c, string l, string p, double b, bool s) : User(i, n, c), libCardNum(l), pin(p), accountBalance(b), accountStatus(s){}
Librarian::Librarian(string i, string n, string c, string p) : User(i, n, c), password(p){}
Admin::Admin(string i, string n, string c, string p) : User(i, n, c), password(p){}
