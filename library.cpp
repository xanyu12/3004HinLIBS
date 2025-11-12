#include "library.h"

Library::Library(){
    numUsers = 0;
    numStaff = 0;
    numAdmin = 0;
}

Library::~Library(){}

void Library::populateUsers(){
    Patron p1("julia74", "Julia Salvatore", "101000001", "1234", "julia1974@gmail.com", 0.0, true);
    Patron p2("nominomi", "Naomi Carthen", "101000002", "2345", "ncarthen@gmail.com", 0.0, true);
    Patron p3("pengting", "Elena Peng", "101000003", "3456", "elenap@gmail.com", 0.0, true);
    Patron p4("nene1999", "Nene Leakes", "101000004", "4567", "laneithia@gmail.com", 0.0, true);
    Patron p5("santana", "Bonnie Santana", "101000005", "5678", "bonbon@gmail.com", 0.0, true);
    Librarian p6("jojojoestar", "Jonathan Joestar", "jj@gmail.com", "pa55wd");
    Admin p7("bigmike", "Michael Scott", "mike.scott@gmail.com", "secret!");

    addUser(p1);
    addUser(p2);
    addUser(p3);
    addUser(p4);
    addUser(p5);

    addStaff(p6);

    addAdmin(p7);
}

void Library::loadCatalogue(){
    collection.populate();
}

void Library::addUser(Patron& u){
  if(numUsers < MAX_ARR){
      users[numUsers] = u;
      numUsers++;
  }else{
      cout << "Maximum Users Reached" << endl;
  }
}

void Library::addStaff(Librarian &l){
  if(numStaff < MAX_ARR){
      staff[numStaff] = l;
      numStaff++;
  }else{
      cout << "Maximum Staff Reached" << endl;
  }
}

void Library::addAdmin(Admin &a){
  if(numAdmin < MAX_ARR){
      admin[numAdmin] = a;
      numStaff++;
  }else{
      cout << "Maximum Staff Reached" << endl;
  }
}


CatalogueItem* Library::findItem(string &s){
    return collection.search(s);
}

double Library::calculateFine(Date &d1, Date &d2){
    if(d2 - d1 > LOAN_PERIOD){
        int daysOverdue = (d2 - d1) - LOAN_PERIOD;
        double fine = daysOverdue * 0.50;
        return fine;
    }
    return 0.00;
}

Date Library::getToday(){
    time_t now = time(0);
    tm* localTime = localtime(&now);
    int year = localTime->tm_year + 1900;
    int month =localTime->tm_mon + 1;
    int day = localTime->tm_mday;

    Date today = Date(day, month, year);
    return today;
}

void Library::checkInItem(CatalogueItem &i, User& p){
    Loan* thisLoan = p.getLoanByItem(i);
    Date returnDay = getToday();
    Date loanDay = thisLoan->getLoanDate();
    double total = calculateFine(loanDay, returnDay);
    if(total > 0.00){
        string id = "F" + i.getID() + p.getUserID() + to_string(loanDay.getDay()) + to_string(loanDay.getMonth());
        Fine f(id, total);
        p.addFine(f);
        thisLoan->setFine(total);
    }
    thisLoan->setReturnDate(returnDay);
    i.checkIn();
}

void Library::checkOutItem(CatalogueItem &i, User& p){
    Date loanDay = getToday();
    string id = "L" + i.getID() + p.getUserID() + to_string(loanDay.getDay()) + to_string(loanDay.getMonth());
    Loan newLoan(id, loanDay, 0, 0.0);
    newLoan.setItem(i);
    bool a = p.addLoan(newLoan);
    if(a){
        i.checkOut();
    }
}

void Library::createHold(CatalogueItem &i, User &p){
    string id = "H" + i.getID() + p.getUserID() + to_string(i.getQueueSize());
    Hold h(id, i.getTitle(), p.getUserID(), i.getQueueSize());
    p.addHold(h);
    i.addToQueue(h);
}

void Library::cancelHold(CatalogueItem &i, User &p){
    string t = i.getTitle();
    bool a = p.removeHold(t);
    if(a){
        i.removeFromQueue(t);
    }
}

Librarian* Library::findStaffByName(string &s){
    for(int i = 0; i < numStaff; ++i){
        if(staff[i].getUserID() == s){
            return &staff[i];
        }
    }
    return nullptr;
}

Patron* Library::findUserByNum(string &n){
    for(int i = 0; i < numUsers; ++i){
        if(users[i].getCardNum() == n){
            return &users[i];
        }
    }
    return nullptr;
}

Admin* Library::findAdminByName(string &s){
    for(int i = 0; i < numAdmin; ++i){
        if(admin[i].getUserID() == s){
            return &admin[i];
        }
    }
    return nullptr;
}

