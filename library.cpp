#include "library.h"

Library::Library(){
    numUsers = 0;
    numStaff = 0;
    numAdmin = 0;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/student/3004HinLIBS/PRAChinlibs.db");

    if(!db.open()){
        cout << "CANNOT CONNECT" << endl;
        return;
    }
    cout << "CONNECTED" << endl;
}

Library::~Library(){
    if(db.isOpen()){
        db.close();
    }
}



bool Library::checkInItem(string& itemID, string& userID){
    QSqlQuery query;
    query.prepare("SELECT status FROM catalogue WHERE itemID = :id");
    query.bindValue(":id", QString::fromStdString(itemID));
    query.exec();
    if(query.next()){
        string itemStatus = query.value("status").toString().toStdString();
        if(itemStatus == "Available"){
            query.prepare("SELECT status FROM users WHERE userID = :id");
            query.bindValue(":id", QString::fromStdString(userID));
            query.exec();
            if(query.next()){
                string userStatus = query.value("status").toString().toStdString();
                if(userStatus == "Active"){
                    query.prepare("SELECT currentLoanNum FROM patron WHERE userID = :id");
                    query.bindValue(":id", QString::fromStdString(userID));
                    query.exec();
                    if(query.next()){
                        int userLoan = query.value("currentLoanNum").toInt();
                        if(userLoan <= 3){
                            userLoan++;
                            Date today = getToday();
                            Date due = today + 14;
                            string date1 = today.toString();
                            string date2 = due.toString();

                            query.prepare("UPDATE catalogue SET status = :s WHERE itemID = :d");
                            query.bindValue(":s", "Unavailable");
                            query.bindValue(":d", QString::fromStdString(userID));
                            query.exec();
                            if(!query.next()){
                                cout << "UPDATE CATALOGUE PROBLEM" << endl;
                                return false;
                            }

                            query.prepare("UPDATE patron SET currentLoanNum = :n WHERE userID = :d");
                            query.bindValue(":n", userLoan);
                            query.bindValue(":d", QString::fromStdString(userID));
                            query.exec();
                            if(!query.next()){
                                cout << "UPDATE PATRON PROBLEM" << endl;
                                return false;
                            }

                            query.prepare("INSERT INTO loans VALUES (:itemID, :userID, :loanDate, :dueDate, :returnDate)");
                            query.bindValue(":itemID", QString::fromStdString(itemID));
                            query.bindValue(":userID", QString::fromStdString(userID));
                            query.bindValue(":loanDate", QString::fromStdString(date1));
                            query.bindValue(":dueDate", QString::fromStdString(date2));
                            query.bindValue(":returnDate", "");

                            query.exec();
                            if(!query.next()){
                                cout << "INSERT LOAN PROBLEM" << endl;
                                return false;
                            }
                            return true;
                        }
                        cout << "ERROR: USER AT MAX LOANS" << endl;
                        return false;
                    }else{
                        cout << "ERROR: QUERY" << endl;
                        return false;
                    }
                }else{
                    cout << "ERROR: USER ACCOUNT LOCKED"  << endl;
                    return false;
                }
            }else{
                cout << "ERROR: QUERY" << endl;
                return false;

            }
        }else{
            cout << "ERROR: ITEM UNAVAILABLE" << endl;
            return false;
       }

    }else{
        cout << "ERROR: QUERY" << endl;
        return false;

    }

}
bool Library::checkOutItem(string& itemID, string& userID){
    //update book status
    QSqlQuery query;
    query.prepare("SELECT loanID, dueDate FROM loans WHERE itemID = :itemID AND userID = :userID AND returnDate = :e");
    query.bindValue(":itemID", QString::fromStdString(itemID));
    query.bindValue(":userID", QString::fromStdString(userID));
    query.bindValue(":e", "");
    query.exec();

    if(query.next()){
        string d = query.value("dueDate").toString().toStdString();
        string lID = query.value("loanID").toString().toStdString();

        Date today = getToday();
        query.prepare("UPDATE loans SET returnDate = :r WHERE loanID = :loanID");
        query.bindValue(":r", QString::fromStdString(today.toString()));
        query.bindValue(":loanID", QString::fromStdString(lID));
        query.exec();

        Date dueDate = convertFromString(d);
        double f = calculateFine(dueDate, today);
        if(f > 0.00){
            query.prepare("SELECT balance FROM patron WHERE userID = :u");;
            query.bindValue(":u", QString::fromStdString(userID));
            query.exec();

            double fine = query.value("balance").toDouble();
            double total = fine + f;
            query.prepare("UPDATE patron SET balance = :b WHERE userID = :u");
            query.bindValue(":b", total);
            query.bindValue(":u", QString::fromStdString(userID));
            query.exec();

            query.prepare("INSERT INTO fines VALUES(:l, :a, :s");
            query.bindValue(":l", QString::fromStdString(lID));
            query.bindValue(":a", fine);
            query.bindValue(":s", "UNPAID");
            query.exec();

        }
        query.prepare("SELECT currentLoanNum FROM patron WHERE userID = :id");
        query.bindValue(":id", QString::fromStdString(userID));
        query.exec();
        int loanNum = query.value("currentLoanNum").toInt();
        loanNum++;
        query.prepare("UPDATE patron SET currentLoanNum = :c WHERE userID = :u");
        query.bindValue(":c", loanNum);
        query.bindValue(":u", QString::fromStdString(userID));
        query.exec();
        query.prepare("UPDATE catalogue SET status = :a WHERE itemID = :id");
        query.bindValue(":a", "Available");
        query.bindValue(":id", QString::fromStdString(itemID));
        query.exec();
        return true;

    }else{
        cout << "ERROR: LOAN DATE" << endl;
        return false;
    }
}

bool Library::createHold(string& itemID, string& userID){}
bool Library::cancelHold(string& itemID, string& userID){}


Date Library::convertFromString(string &s){
    string tempD = "";
    tempD += s[0];
    tempD += s[1];
    int d = stoi(tempD);

    string tempM = "";
    tempM += s[3];
    tempM += s[4];
    int m = stoi(tempM);

    string tempY = "";
    tempY += s[6];
    tempY += s[7];
    tempY += s[8];
    tempY += s[0];
    int y = stoi(tempY);

    Date newD = Date(d, m, y);
    return newD;
}


//void Library::populateUsers(){
//    Patron p1("julia74", "Julia Salvatore","julia1974@gmail.com", "101000001", "1234", 0.0, true);
//    Patron p2("nominomi", "Naomi Carthen", "ncarthen@gmail.com", "101000002", "2345", 0.0, true);
//    Patron p3("pengting", "Elena Peng", "elenap@gmail.com", "101000003", "3456",  0.0, true);
//    Patron p4("nene1999", "Nene Leakes", "laneithia@gmail.com", "101000004", "4567", 0.0, true);
//    Patron p5("santana", "Bonnie Santana", "bonbon@gmail.com", "101000005", "5678",  0.0, true);
//    Librarian p6("jojojoestar", "Jonathan Joestar", "jj@gmail.com", "pa55wd");
//    Admin p7("bigmike", "Michael Scott", "mike.scott@gmail.com", "secret!");

//    addUser(p1);
//    addUser(p2);
//    addUser(p3);
//    addUser(p4);
//    addUser(p5);

//    addStaff(p6);

//    addAdmin(p7);

//    cout << "Populated Users" << endl;
//}

//void Library::loadCatalogue(){
//    collection.populate();

//    cout << "Loaded Catalogue" << endl;
//}

//void Library::addUser(Patron& u){
//  if(numUsers < MAX_ARR){
//      cout << "Adding User: " + u.getUserID()<< endl;
//      users[numUsers] = u;
//      numUsers++;
//  }else{
//      cout << "Maximum Users Reached" << endl;
//  }
//}

//void Library::addStaff(Librarian &l){
//  if(numStaff < MAX_ARR){
//      cout << "Adding Staff: " + l.getUserID() << endl;
//      staff[numStaff] = l;
//      numStaff++;
//  }else{
//      cout << "Maximum Staff Reached" << endl;
//  }
//}

//void Library::addAdmin(Admin &a){
//  if(numAdmin < MAX_ARR){
//      cout << "Adding Admin: " + a.getUserID() << endl;
//      admin[numAdmin] = a;
//      numAdmin++;
//  }else{
//      cout << "Maximum Staff Reached" << endl;
//  }
//}


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

//bool Library::checkInItem(CatalogueItem* i, User* u){
//    string s = u->getUserID();
//    Patron* p = findUserByName(s);
//    Loan* thisLoan = p->getLoanByItem(*i);
//    Date returnDay = getToday();
//    Date loanDay = thisLoan->getLoanDate();
//    double total = calculateFine(loanDay, returnDay);
//    if(total > 0.00){
//        string id = "F" + i->getID() + p->getUserID() + to_string(loanDay.getDay()) + to_string(loanDay.getMonth());
//        Fine f(id, total);
//        p->addFine(f);
//        thisLoan->setFine(total);
//    }
//    thisLoan->setReturnDate(returnDay);
//    i->checkIn();
//    return true;
//}

//bool Library::checkOutItem(CatalogueItem* i, User* u){
//    string s = u->getUserID();
//    Patron* p = findUserByName(s);
//    cout << "Checking out item: " + i->getTitle() + " for " + p->getUserID() << endl;
//    if(i->getCirculationStatus() == Status::Available && p->getAccountStatus() == "Active"){
//        cout << "Borrow Available" << endl;
//        Date loanDay = getToday();
//        string id = "L" + i->getID() + p->getUserID() + to_string(loanDay.getDay()) + to_string(loanDay.getMonth());
//        Loan newLoan(id, loanDay, 0, 0.0);
//        newLoan.setItem(i);
//        bool a = p->addLoan(newLoan);
//        if(a == true){
//            cout << "CHECKED OUT" << endl;
//            i->checkOut();
//        }else{
//            return false;
//        }
//        return true;
//    }else{
//        return false;
//    }
//}

bool Library::createHold(CatalogueItem* i, User* u){
    string s = u->getUserID();
    Patron* p = findUserByName(s);
    string id = "H" + i->getID() + p->getUserID() + to_string(i->getQueueSize());
    Hold h(id, i->getTitle(), p->getUserID(), i->getQueueSize()+1);
    p->addHold(h);
    i->addToQueue(h);
    return true;
}

bool Library::cancelHold(CatalogueItem* i, User* u){
    string s = u->getUserID();
    Patron* p = findUserByName(s);
    string t = i->getTitle();
    bool a = p->removeHold(t);
    if(a){
        i->removeFromQueue(t);
    }else{
        return false;
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

