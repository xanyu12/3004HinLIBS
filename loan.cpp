#include "loan.h"

Loan::Loan(string i, Date l, Date r, double f){
    loanID = i;
    loanDate = l;
    returnDate = r;
    fineIncurred = f;
}
Loan::~Loan(){}

string Loan::getLoanID(){
    return loanID;
}
Date Loan::getLoanDate(){
    return loanDate;
}
Date Loan::getReturnDate(){
    return returnDate;
}
double Loan::getFineIncurred(){
    return fineIncurred;
}
