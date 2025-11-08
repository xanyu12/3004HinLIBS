#ifndef PATRON_H
#define PATRON_H

#include "user.h"
#include "loan.h"
#include "defs.h"

class Patron : public User{
public:
    Patron();
    ~Patron();

 private:
    string patronID;
    string name;
    string contact;
    double accountBalance;
    bool accountStatus;
    Loan loanArr[MAX_LOANS];

};

#endif // PATRON_H
