#include "loan.h"

Loan::Loan(string i, Date l, Date r, double f){
    loanID = i;
    loanDate = l;
    returnDate = r;
    fineIncurred = f;
}
Loan::~Loan(){}

void Loan::setItem(CatalogueItem* i){
    cout << "NEW LOAN " + i->getTitle() << endl;
    item = i;
}

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

void Loan::setFine(double f){
    fineIncurred = f;
}

void Loan::setReturnDate(Date &d){
    returnDate = d;
}

CatalogueItem* Loan::getItem(){
    return item;
}
