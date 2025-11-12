#ifndef LOAN_H
#define LOAN_H

#include "defs.h"
#include "catalogueItem.h"

class Loan{
public:
    Loan(string="", Date=Date(), Date=Date(), double=0.0);
    ~Loan();

    string getLoanID();
    Date getLoanDate();
    Date getReturnDate();
    double getFineIncurred();

    void setItem(CatalogueItem& item);
    void setReturnDate(Date& d);
    void setFine(double f);
    CatalogueItem* getItem();

private:
    string loanID;
    CatalogueItem* item;
    Date loanDate;
    Date returnDate;
    double fineIncurred;


};

#endif // LOAN_H
