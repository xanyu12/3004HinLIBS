#ifndef USER_H
#define USER_H

#include "defs.h"
#include "loan.h"
#include "fine.h"

class User
{
public:
    User(string="", string="", string="");
    virtual ~User();

    void addUser();
    void populate();

private:
    string userID;
    string name;
    string contact;
};

class Patron : public User{
public:
    Patron(string i, string n, string c, string l, string p, double b, bool s);

    string getCardNum();
    string getPin();
    double getAccountBalance();

 private:
    string libCardNum;
    string pin;
    double accountBalance;
    bool accountStatus;
    Loan loanArr[MAX_LOANS];
    Fine paymentHistory[MAX_ARR];

};

class Librarian : public User{
public:
    Librarian(string i, string n, string c, string p);

    string getPassword();

private:
    string password;
};

class Admin : public User{
public:
    Admin(string i, string n, string c, string p);

    string getPassword();
private:
    string password;
};

#endif // USER_H
