#ifndef USER_H
#define USER_H

#include "defs.h"
#include "loan.h"

class User
{
public:
    User(string="", string="", string="", string="");
    ~User();

    void addUser();
    void populate();

private:
    string userID;
    string name;
    string password;
    string contact;
};

class Patron : public User{
public:
    Patron(string i, string n, string p, string c, double b, bool s);
    ~Patron();

 private:
    double accountBalance;
    bool accountStatus;
    Loan loanArr[MAX_LOANS];

};

#endif // USER_H
