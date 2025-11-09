#include "fine.h"

Fine::Fine(string i, double a){
    fineID = i;
    amount = a;
    status=false;
}

Fine::~Fine(){}

string Fine::getFineID(){
    return fineID;
}
double Fine::getAmount(){
    return amount;
}
bool Fine::getStatus(){
    return status;
}

void Fine::updateStatus(){
    if(status == false){
        status = true;
    }
}
