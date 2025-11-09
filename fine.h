#ifndef FINE_H
#define FINE_H

#include "defs.h"

class Fine{
public:
    Fine(string="", double=0.0);
    ~Fine();
    string getFineID();
    double getAmount();
    bool getStatus();

    void updateStatus();

private:
    string fineID;
    double amount;
    bool status;

};

#endif // FINE_H
