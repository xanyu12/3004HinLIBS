#include "fine.h"

Fine::Fine(string i, double a, string s){
    fineID = i;
    amount = a;
    status = s;
}

Fine::~Fine(){}

string Fine::getFineID(){
    return fineID;
}
double Fine::getAmount(){
    return amount;
}
string Fine::getStatus(){
    return status;
}
