#include "library.h"

Library::Library(){numUsers = 0;}

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
    addUser(p6);
    addUser(p7);
}

void Library::loadCatalogue(){
    collection.populate();
}

void Library::addUser(User& u){
  if(numUsers < MAX_ARR){
      users[numUsers] = u;
      numUsers++;
  }else{
      cout << "Maximum Users Reached" << endl;
  }
}

void Library::searchCatalogue(string &s){
    collection.search(s);
}

double Library::calculateFine(Date &d1, Date &d2){
    if(d2 - d1 > LOAN_PERIOD){
        int daysOverdue = (d2 - d1) - LOAN_PERIOD;
        double fine = daysOverdue * 0.50;
        return fine;
    }
    return 0.00;
}

void Library::checkInItem(CatalogueItem &i, Patron& p){
    Loan* thisLoan = p.getLoan(i);
    Date returnDay(12, 12, 12);
    Date loanDay = thisLoan->getLoanDate();
    double total = calculateFine(loanDay, returnDay);
    if(total > 0.00){
        string id = i.getTitle() + p.getUserID() + to_string(loanDay.getDay()) + to_string(loanDay.getMonth());
        Fine f("", total);
        p.addFine(f);
        thisLoan->setFine(total);
    }
    thisLoan->setReturnDate(returnDay);
    i.checkIn();
}

void Library::checkOutItem(CatalogueItem &i, Patron& p){
    Date loanDay(0,0,0);
    string id = i.getTitle() + p.getUserID() + to_string(loanDay.getDay()) + to_string(loanDay.getMonth());
    Loan newLoan(id, Date(0,0,0), 0, 0.0);
    i.checkOut();
    p.addLoan(newLoan);
}
