#ifndef USER_H
#define USER_H

#include "defs.h"
#include "loan.h"
#include "fine.h"
#include "hold.h"

class User
{
public:
    User(string="", string="", string="");
    ~User();

    string getUserID();

private:
    string userID;
    string name;
    string contact;
};

class Patron : public User{
public:
    Patron(string="", string="", string="", string="", string="", double=0.0, bool="");

    string getCardNum();
    string getPin();
    double getAccountBalance();

    int getNumLoans();
    int getNumHolds();

    bool addLoan(Loan& l);
    Loan* getLoanByIdx(int n);
    Loan* getLoanByItem(CatalogueItem& c);

    void payFine(Fine& f);
    void addFine(Fine& f);

    void addHold(Hold& h);
    bool removeHold(Hold& h);
    Hold* getHoldByIdx(int n);


 private:
    string libCardNum;
    string pin;
    double accountBalance;
    bool accountStatus;
    Loan loanArr[MAX_LOANS];
    Fine paymentHistory[MAX_ARR];
    Hold holdArr[MAX_ARR];

    int numLoans;
    int numFines;
    int numHolds;
};

class Librarian : public User{
public:
    Librarian(string="", string="", string="", string="");

    string getPassword();

private:
    string password;
};

class Admin : public User{
public:
    Admin(string="", string="", string="", string="");

    string getPassword();
private:
    string password;
};

#endif // USER_H
