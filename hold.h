#ifndef HOLD_H
#define HOLD_H

#include "defs.h"

class Hold{
public:
    Hold(string id="");

    string getHoldID();

private:
    string holdID;
};

#endif // HOLD_H
