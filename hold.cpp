#include "hold.h"

Hold::Hold(string id, string t, string o, int p): holdID(id), title(t), owner(o), position(p){}

string Hold::getHoldID(){
    return holdID;
}

string Hold::getItemTitle(){
    return title;
}

string Hold::getOwner(){
    return owner;
}

int Hold::getPosition(){
    return position;
}

void Hold::updatePosition(){
    position = position - 1;
}
