#include "library.h"

Library::Library(){
    numUsers = 0;
    numStaff = 0;
    numAdmin = 0;
}

Library::~Library(){}

void Library::populateUsers(){
    Patron p1("julia74", "Julia Salvatore","julia1974@gmail.com", "101000001", "1234", 0.0, true);
    Patron p2("nominomi", "Naomi Carthen", "ncarthen@gmail.com", "101000002", "2345", 0.0, true);
    Patron p3("pengting", "Elena Peng", "elenap@gmail.com", "101000003", "3456",  0.0, true);
    Patron p4("nene1999", "Nene Leakes", "laneithia@gmail.com", "101000004", "4567", 0.0, true);
    Patron p5("santana", "Bonnie Santana", "bonbon@gmail.com", "101000005", "5678",  0.0, true);
    Librarian p6("jojojoestar", "Jonathan Joestar", "jj@gmail.com", "pa55wd");
    Admin p7("bigmike", "Michael Scott", "mike.scott@gmail.com", "secret!");

    addUser(p1);
    addUser(p2);
    addUser(p3);
    addUser(p4);
    addUser(p5);

    addStaff(p6);

    addAdmin(p7);

    cout << "Populated Users" << endl;
}

void Library::loadCatalogue(){
    collection.populate();

    cout << "Loaded Catalogue" << endl;
}

void Library::addUser(Patron& u){
  if(numUsers < MAX_ARR){
      cout << "Adding User: " + u.getUserID()<< endl;
      users[numUsers] = u;
      numUsers++;
  }else{
      cout << "Maximum Users Reached" << endl;
  }
}

void Library::addStaff(Librarian &l){
  if(numStaff < MAX_ARR){
      cout << "Adding Staff: " + l.getUserID() << endl;
      staff[numStaff] = l;
      numStaff++;
  }else{
      cout << "Maximum Staff Reached" << endl;
  }
}

void Library::addAdmin(Admin &a){
  if(numAdmin < MAX_ARR){
      cout << "Adding Admin: " + a.getUserID() << endl;
      admin[numAdmin] = a;
      numAdmin++;
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

bool Library::checkInItem(CatalogueItem* i, User* u){
    string s = u->getUserID();
    Patron* p = findUserByName(s);
    Loan* thisLoan = p->getLoanByItem(*i);
    Date returnDay = getToday();
    Date loanDay = thisLoan->getLoanDate();
    double total = calculateFine(loanDay, returnDay);
    if(total > 0.00){
        string id = "F" + i->getID() + p->getUserID() + to_string(loanDay.getDay()) + to_string(loanDay.getMonth());
        Fine f(id, total);
        p->addFine(f);
        thisLoan->setFine(total);
    }
    thisLoan->setReturnDate(returnDay);
    i->checkIn();
    return true;
}

bool Library::checkOutItem(CatalogueItem* i, User* u){
    string s = u->getUserID();
    Patron* p = findUserByName(s);
    cout << "Checking out item: " + i->getTitle() + " for " + p->getUserID() << endl;
    if(i->getCirculationStatus() == Status::Available && p->getAccountStatus() == "Active"){
        cout << "Borrow Available" << endl;
        Date loanDay = getToday();
        string id = "L" + i->getID() + p->getUserID() + to_string(loanDay.getDay()) + to_string(loanDay.getMonth());
        Loan newLoan(id, loanDay, 0, 0.0);
        newLoan.setItem(i);
        bool a = p->addLoan(newLoan);
        if(a == true){
            cout << "CHECKED OUT" << endl;
            i->checkOut();
        }
        return true;
    }else{
        return false;
    }
}

bool Library::createHold(CatalogueItem* i, User* p){
    string id = "H" + i->getID() + p->getUserID() + to_string(i->getQueueSize());
    Hold h(id, i->getTitle(), p->getUserID(), i->getQueueSize());
    p->addHold(h);
    i->addToQueue(h);
    return true;
}

bool Library::cancelHold(CatalogueItem* i, User* p){
    string t = i->getTitle();
    bool a = p->removeHold(t);
    if(a){
        i->removeFromQueue(t);
    }
    return true;
}

Librarian* Library::findStaffByName(string &s){
    cout << "Finding Staff: " + s << endl;
    for(int i = 0; i < numStaff; ++i){
        if(staff[i].getUserID() == s){
            return &staff[i];
        }
    }
    return nullptr;
}

Patron* Library::findUserByNum(string &n){
    cout << "Finding User: " + n << endl;
    for(int i = 0; i < numUsers; ++i){
        if(users[i].getCardNum() == n){
            return &users[i];
        }
    }
    return nullptr;
}

Patron* Library::findUserByName(string &n){
    cout << "Finding User: " + n << endl;
    for(int i = 0; i < numUsers; ++i){
        if(users[i].getUserID() == n){
            return &users[i];
        }
    }
    return nullptr;
}

Catalogue Library::getCatalogue(){
    return collection;
}

Admin* Library::findAdminByName(string &s){
    cout << "Finding Admin: " + s << endl;
    for(int i = 0; i < numAdmin; ++i){
        if(admin[i].getUserID() == s){
            return &admin[i];
        }
    }
    return nullptr;
}

