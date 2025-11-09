#ifndef FINE_H
#define FINE_H

#include "defs.h"

class Fine{
public:
    Fine(string="", double=0.0, string="");
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
