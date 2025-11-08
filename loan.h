#ifndef LOAN_H
#define LOAN_H

#include "defs.h"

class Loan{
public:
    Loan();
    ~Loan();

private:
    string loanID;
    Date loanDate;
    Date dueDate;
    Date returnDate;
    double fineIncurred;


};

#endif // LOAN_H
