#ifndef FINE_H
#define FINE_H

#include "defs.h"

class Fine{
public:
    Fine();
    ~Fine();
    string getFineID();
    double getAmount();
    string getStatus();

private:
    string fineID;
    double amount;
    string status;

};

#endif // FINE_H
