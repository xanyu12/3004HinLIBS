#ifndef LOAN_H
#define LOAN_H

#include "defs.h"

class Loan{
public:
    Loan(string="", Date=Date(), Date=Date(), double=0.0);
    ~Loan();

    string getLoanID();
    Date getLoanDate();
    Date getReturnDate();
    double getFineIncurred();


private:
    string loanID;
    Date loanDate;
    Date returnDate;
    double fineIncurred;


};

#endif // LOAN_H
