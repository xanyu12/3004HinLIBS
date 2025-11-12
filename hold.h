#ifndef HOLD_H
#define HOLD_H

#include "defs.h"

class Hold{
public:
    Hold(string id="", string="", string="", int=0);

    string getHoldID();
    string getItemTitle();
    string getOwner();
    int getPosition();

    void updatePosition();

private:
    string holdID;
    string title;
    string owner;
    int position;
};

#endif // HOLD_H
