#include "user.h"

User::User(string i, string n, string c){
    userID = i;
    name = n;
    contact = c;
}

User::~User(){}

string User::getUserID(){
    return userID;
}

Patron::Patron(string i, string n, string c, string l, string p, double b, bool s)
    : User(i, n, c), libCardNum(l), pin(p), accountBalance(b), accountStatus(s){
    numFines = 0;
    numHolds = 0;
    numLoans = 0;
}

string Patron::getCardNum(){
    return libCardNum;
}

string Patron::getPin(){
    return pin;
}

double Patron::getAccountBalance(){
    return accountBalance;
}

int Patron::getNumLoans(){
    return numLoans;
}

bool Patron::addLoan(Loan &l){
    if(numLoans < MAX_LOANS){
        loanArr[numLoans] = l;
        numLoans++;
        return true;
    }else{
        cout << "Maximum Loans" << endl;
        return false;
    }
}

void Patron::addFine(Fine &f){
    if(numFines < MAX_ARR){
        paymentHistory[numFines] = f;
        numFines++;
    }else{
        cout << "Maximum Fines" << endl;
    }
}

void Patron::addHold(Hold &h){
    if(numHolds < MAX_ARR){
        holdArr[numHolds] = h;
        numHolds++;
    }else{
        cout << "Maximum Holds" << endl;
    }
}

bool Patron::removeHold(string& s){
    int idx = -1;
    for(int i = 0; i < numHolds; ++i){
        if(holdArr[i].getItemTitle() == s){
            idx = i;
            break;
        }
    }

    if(idx != -1){
        for(int j = idx; j < numHolds - 1; ++j){
            holdArr[j] = holdArr[j+1];
        }
        numHolds--;
        return true;
    }else{
        return false;
    }

}

void Patron::payFine(Fine &f){
    f.updateStatus();
}

Loan* Patron::getLoanByIdx(int n){
    return &loanArr[n];

}

Hold* Patron::getHoldByIdx(int n){
    return &holdArr[n];
}

Loan* Patron::getLoanByItem(CatalogueItem &c){
    for(int i = 0; i < numLoans; ++i){
        if(loanArr[i].getItem()->getID() == c.getID()){
            return &loanArr[i];
        }
    }
    return nullptr;
}

Librarian::Librarian(string i, string n, string c, string p)
    : User(i, n, c), password(p){}

string Librarian::getPassword(){
    return password;
}

Admin::Admin(string i, string n, string c, string p)
    : User(i, n, c), password(p){}

string Admin::getPassword(){
    return password;
}

