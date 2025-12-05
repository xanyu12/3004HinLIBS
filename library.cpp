#include "library.h"

Library::Library(){
    numUsers = 0;
    numStaff = 0;
    numAdmin = 0;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/student/3004HinLIBS/hinlibs.db");

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

bool Library::checkOutItem(string& itemID, string& userID){
    QSqlQuery query;
    query.prepare("SELECT * FROM catalogue WHERE title = :id");
    query.bindValue(":id", QString::fromStdString(itemID));
    query.exec();

    if(!query.next()){
        qDebug() << "ERROR: Item not found:" << query.lastError();
        return false;
    }
    itemID = query.value("itemID").toString().toStdString();
    string itemStatus = query.value("status").toString().toStdString();

    if(itemStatus != "Available"){
        cout << "ERROR: ITEM UNAVAILABLE" << endl;
        return false;
    }

    query.prepare("SELECT status FROM patron WHERE userID = :id");
    query.bindValue(":id", QString::fromStdString(userID));
    query.exec();
    if(!query.next()){
        return false;
    }
    string userStatus = query.value("status").toString().toStdString();
    cout << userStatus << endl;

    if(userStatus != "Active"){
        cout << "ERROR: USER INACTIVE" << endl;
    }
    query.prepare("SELECT currentLoanNum FROM patron WHERE userID = :id");
    query.bindValue(":id", QString::fromStdString(userID));
    query.exec();
    if(!query.next()){
        return false;
    }

    int userLoan = query.value("currentLoanNum").toInt();
    cout << userLoan << endl;
    if(userLoan <= 3){
        cout << "WE SHOULD BE GOOD" << endl;
        userLoan++;
        Date today = getToday();
        Date due = today + 14;
        string date1 = today.toString();
        string date2 = due.toString();

        query.prepare("UPDATE catalogue SET status = :s WHERE itemID = :d");
        query.bindValue(":s", "Unavailable");
        query.bindValue(":d", QString::fromStdString(itemID));
        query.exec();
        cout << "SUCCESS CATALOGUE?" << endl;

        query.prepare("UPDATE patron SET currentLoanNum = :n WHERE userID = :d");
        query.bindValue(":n", userLoan);
        query.bindValue(":d", QString::fromStdString(userID));
        query.exec();
        cout << "SUCCESS PATRON" << endl;

        query.prepare("INSERT INTO loans (itemID, userID, loanDate, dueDate) VALUES (:itemID, :userID, :loanDate, :dueDate)");
        query.bindValue(":itemID", QString::fromStdString(itemID));
        query.bindValue(":userID", QString::fromStdString(userID));
        query.bindValue(":loanDate", QString::fromStdString(date1));
        query.bindValue(":dueDate", QString::fromStdString(date2));
        query.exec();
        cout << "SUCCESS INSERT" << endl;

        return true;
    }else{
        cout << "ERROR: MAX LOANS" << endl;
    }

    return false;
}
bool Library::checkInItem(string& itemID, string& userID){
    //update book status
    QSqlQuery query;
    query.prepare("SELECT * FROM catalogue WHERE title = :id");
    query.bindValue(":id", QString::fromStdString(itemID));
    query.exec();

    if(!query.next()){
        qDebug() << "ERROR: Item not found:" << query.lastError();
        return false;
    }
    itemID = query.value("itemID").toString().toStdString();
    query.prepare("SELECT * FROM loans WHERE itemID = :itemID AND userID = :userID AND returnDate IS NULL");
    query.bindValue(":itemID", QString::fromStdString(itemID));
    query.bindValue(":userID", QString::fromStdString(userID));
    query.exec();

    if(!query.next()){
        qDebug() << "ERROR: Loan not found:" << query.lastError();
        return false;
    }
    string d = query.value("dueDate").toString().toStdString();
    string lID = query.value("loanID").toString().toStdString();
    cout << "Due Date: " + d << endl;
    cout << lID << endl;

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
        if(!query.next()){
            cout << "Patron not found" << endl;
            return false;
        }
        double fine = query.value("balance").toDouble();
        double total = fine + f;
        query.prepare("UPDATE patron SET balance = :b WHERE userID = :u");
        query.bindValue(":b", total);
        query.bindValue(":u", QString::fromStdString(userID));
        query.exec();
        cout << "SUCCESS PATRON" << endl;

        query.prepare("INSERT INTO fines (loanID, amount, status) VALUES(:l, :a, :s)");
        query.bindValue(":l", QString::fromStdString(lID));
        query.bindValue(":a", fine);
        query.bindValue(":s", "UNPAID");
        query.exec();
        cout << "SUCCESS FINES" << endl;

    }
    query.prepare("SELECT currentLoanNum FROM patron WHERE userID = :id");
    query.bindValue(":id", QString::fromStdString(userID));
    query.exec();
    if(!query.next()){
        cout << "USER ERROR" << endl;
        return false;
    }
    int loanNum = query.value("currentLoanNum").toInt();
    cout << loanNum << endl;
    if(loanNum > 0){
        loanNum--;
    }
    query.prepare("UPDATE patron SET currentLoanNum = :c WHERE userID = :u");
    query.bindValue(":c", loanNum);
    query.bindValue(":u", QString::fromStdString(userID));
    query.exec();
    cout << "SUCCESS PATRON" << endl;
    query.prepare("UPDATE catalogue SET status = :a WHERE itemID = :id");
    query.bindValue(":a", "Available");
    query.bindValue(":id", QString::fromStdString(itemID));
    query.exec();
    cout << "SUCCESS CATALOGUE" << endl;
    return true;
}

bool Library::createHold(string& itemID, string& userID){
    //create hold
    //add user to item queue
    //increase user queue size
    QSqlQuery query;
    query.prepare("SELECT * FROM catalogue WHERE title = :id");
    query.bindValue(":id", QString::fromStdString(itemID));
    query.exec();

    if(!query.next()){
        qDebug() << "ERROR: Item not found:" << query.lastError();
        return false;
    }
    itemID = query.value("itemID").toString().toStdString();

    query.prepare("SELECT availability FROM catalogue WHERE itemID = :i");
    query.bindValue(":i", QString::fromStdString(itemID));
    query.exec();
    if(!query.next()){
        return false;
    }
    string avail = query.value("availability").toString().toStdString();
    if(avail == "Available"){
        return false;
    }

    query.prepare("SELECT queueSize FROM catalogue WHERE itemID = :i");
    query.bindValue(":i", QString::fromStdString(itemID));
    query.exec();
    if(!query.next()){
        return false;
    }
    int queueSize = query.value("queueSize").toInt();
    queueSize++;

    query.prepare("INSERT INTO holds (itemID, userID, position) VALUES (:itemID, :userID, :pos)");
    query.bindValue(":itemID", QString::fromStdString(itemID));
    query.bindValue(":userID", QString::fromStdString(userID));
    query.bindValue(":pos", queueSize);
    query.exec();

    query.prepare("UPDATE catalogue SET queueSize = :num WHERE itemID = :i");
    query.bindValue(":num", queueSize);
    query.bindValue(":i", QString::fromStdString(itemID));
    query.exec();

    query.prepare("UPDATE patron SET currentHoldNum = currentHoldNum + 1 WHERE userID = :u");
    query.bindValue(":u", QString::fromStdString(userID));
    query.exec();

    return true;
}
bool Library::cancelHold(string& itemID, string& userID){
    //remove user from item queue
    //update item queue
    //reduce user queue size
    QSqlQuery query;
    query.prepare("SELECT * FROM catalogue WHERE title = :id");
    query.bindValue(":id", QString::fromStdString(itemID));
    query.exec();

    if(!query.next()){
        qDebug() << "ERROR: Item not found:" << query.lastError();
        return false;
    }
    itemID = query.value("itemID").toString().toStdString();
    query.prepare("SELECT position from holds WHERE itemID = :i and userID = :u");
    query.bindValue(":i", QString::fromStdString(itemID));
    query.bindValue(":u", QString::fromStdString(userID));
    query.exec();
    if(!query.next()){
        return false;
    }
    int position = query.value("position").toInt();
    query.prepare("UPDATE holds SET position = position - 1 WHERE itemID = :i AND position > :pos");
    query.bindValue(":i", QString::fromStdString(itemID));
    query.bindValue(":pos", position);
    query.exec();

    query.prepare("UPDATE catalogue SET queueSize = queueSize - 1 WHERE itemID = :i");
    query.bindValue(":i", QString::fromStdString(itemID));
    query.exec();

    query.prepare("DELETE FROM holds WHERE itemID = :i and userID = :u");
    query.bindValue(":i", QString::fromStdString(itemID));
    query.bindValue(":u", QString::fromStdString(userID));
    query.exec();

    query.prepare("UPDATE patron SET currentHoldNum = currentHoldNum - 1 WHERE userID = :u");
    query.bindValue(":u", QString::fromStdString(userID));
    query.exec();

    return true;
}

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
    tempY += s[9];
    int y = stoi(tempY);

    Date newD = Date(d, m, y);
    return newD;
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

Status Library::translateToStatus(string& s){
    if(s == "Available"){
        return Status::Available;
    }else if(s == "Unavailable"){
        return Status::Unavailable;
    }else if(s == "Missing"){
        return Status::Missing;
    }else if(s == "Withdrawn"){
        return Status::Withdrawn;
    }else{
        return Status::Unavailable;
    }
}

int Library::getCatalogueSize(){
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM catalogue");
    query.exec();
    if(!query.next()){
        return -1;
    }
    int ans = query.value(0).toInt();
    return ans;
}

QString Library::getItem(int i, int j){
    QSqlQuery query;
    query.prepare("SELECT * FROM catalogue LIMIT 1 OFFSET :i");
    query.bindValue(":i", i);
    query.exec();
    if(!query.next()){
        return nullptr;
    }
    QString ans = query.value(j).toString();
    return ans;
}

QString Library::getLoanTitle(int i, string& userID){
    QSqlQuery query;
    query.prepare("SELECT * FROM loans l, catalogue c WHERE l.userID = :u AND l.returnDate IS NULL AND l.itemID = c.itemID LIMIT 1 OFFSET :i ");
    query.bindValue(":u", QString::fromStdString(userID));
    query.bindValue(":i", i);
    query.exec();
    if(!query.next()){
        return nullptr;
    }
    QString ans = query.value("title").toString();
    cout  << ans.toStdString() << endl;
    return ans;
}

int Library::getDaysLeft(int i, string &userID){
    QSqlQuery query;
    query.prepare("SELECT * FROM loans WHERE userID = :u AND returnDate IS NULL LIMIT 1 OFFSET :i");
    query.bindValue(":u", QString::fromStdString(userID));
    query.bindValue(":i", i);
    query.exec();
    if(!query.next()){
        return -1;
    }
    string d = query.value("dueDate").toString().toStdString();
    Date due = convertFromString(d);
    cout << due.toString() << endl;
    Date today = getToday();
    int num = due - today;
    cout << num << endl;
    return num;
}

QString Library::getLoanDate(int i, string &userID){
    QSqlQuery query;
    query.prepare("SELECT * FROM loans WHERE userID = :u AND returnDate IS NULL LIMIT 1 OFFSET :i");
    query.bindValue(":u", QString::fromStdString(userID));
    query.bindValue(":i", i);
    query.exec();
    if(!query.next()){
        return nullptr;
    }
    QString ans = query.value("dueDate").toString();
    return ans;
}

QString Library::getHoldTitle(int i, string &userID){
    QSqlQuery query;
    query.prepare("SELECT * FROM holds l, catalogue c WHERE l.userID = :u AND l.itemID = c.itemID LIMIT 1 OFFSET :i ");
    query.bindValue(":u", QString::fromStdString(userID));
    query.bindValue(":i", i);
    query.exec();
    if(!query.next()){
        return nullptr;
    }
    QString ans = query.value("title").toString();
    return ans;
}

QString Library::getHoldPos(int i, string &userID){
    QSqlQuery query;
    query.prepare("SELECT * FROM holds WHERE userID = :u LIMIT 1 OFFSET :i");
    query.bindValue(":u", QString::fromStdString(userID));
    query.bindValue(":i", i);
    query.exec();
    if(!query.next()){
        return nullptr;
    }
    QString ans = query.value("position").toString();
    return ans;
}

Librarian* Library::findStaffByName(string& s){
    QSqlQuery query;
    query.prepare("SELECT * FROM users u, librarians l WHERE u.userID = :s AND u.userID = l.userID");
    query.bindValue(":s", QString::fromStdString(s));
    query.exec();
    if(!query.next()){
        return nullptr;
    }
    string name = query.value("name").toString().toStdString();
    string password = query.value("password").toString().toStdString();
    string contact = query.value("contact").toString().toStdString();
    Librarian* l = new Librarian(s, name, contact, password);
    return l;
}

Admin* Library::findAdminByName(string& s){
    QSqlQuery query;
    query.prepare("SELECT * FROM users u, admins l WHERE u.userID = :s AND u.userID = l.userID");
    query.bindValue(":s", QString::fromStdString(s));
    query.exec();
    if(!query.next()){
        return nullptr;
    }
    string name = query.value("name").toString().toStdString();
    string password = query.value("password").toString().toStdString();
    string contact = query.value("contact").toString().toStdString();
    Admin* l = new Admin(s, name, contact, password);
    return l;
}

Patron* Library::findUserByNum(string& n){
    QSqlQuery query;
    query.prepare("SELECT * FROM patron p, users u WHERE p.cardNumber = :n AND u.userID = p.userID");
    query.bindValue(":n", QString::fromStdString(n));
    query.exec();
    if(!query.next()){
       return nullptr;
    }
    string userID = query.value("userID").toString().toStdString();
    string name = query.value("name").toString().toStdString();
    string contact = query.value("contact").toString().toStdString();
    string pin = query.value("pin").toString().toStdString();
    double balance = query.value("balance").toDouble();
    string status = query.value("status").toString().toStdString();
    Patron* p = new Patron(userID, name, contact, n, pin, balance, status);
    return p;
}
Patron* Library::findUserByName(string & s){
    QSqlQuery query;
    query.prepare("SELECT * FROM users u, patron l WHERE u.userID = :s AND u.userID = l.userID");
    query.bindValue(":s", QString::fromStdString(s));
    query.exec();
    if(!query.next()){
        return nullptr;
    }
    string name = query.value("name").toString().toStdString();
    string contact = query.value("contact").toString().toStdString();
    string libCard = query.value("cardNumber").toString().toStdString();
    string pin = query.value("pin").toString().toStdString();
    double balance = query.value("balance").toDouble();
    string status = query.value("status").toString().toStdString();
    Patron* l = new Patron(s, name, contact, libCard, pin, balance, status);
    return l;
}

int Library::getNumHolds(string &userID){
    QSqlQuery query;
    query.prepare("SELECT * FROM patron WHERE userID = :u");
    query.bindValue(":u", QString::fromStdString(userID));
    query.exec();
    if(!query.next()){
        cout << "ERROR: USER NOT FOUND" << endl;
        return -1;
    }
    int num = query.value("currentHoldNum").toInt();
    return num;
}

int Library::getNumLoans(string &userID){
    QSqlQuery query;
    query.prepare("SELECT * FROM patron WHERE userID = :u");
    query.bindValue(":u", QString::fromStdString(userID));
    query.exec();
    if(!query.next()){
        cout << "ERROR: USER NOT FOUND" << endl;
        return -1;
    }
    int num = query.value("currentLoanNum").toInt();
    return num;
}

bool Library::addItem(CatalogueItem *c, string& type){
    string condition = c->translateCondition(c->getCondition());
    string status = c->translateStatus(c->getCirculationStatus());
    QSqlQuery query;
    query.prepare("INSERT INTO catalogue VALUES (:id, :title, :creator, :type, :year, :con, :form, :stat, :size)");
    query.bindValue(":id", QString::fromStdString(c->getID()));
    query.bindValue(":title", QString::fromStdString(c->getTitle()));
    query.bindValue(":creator", QString::fromStdString(c->getCreator()));
    query.bindValue(":type", QString::fromStdString(type));
    query.bindValue(":year", c->getPublicationYear());
    query.bindValue(":con", QString::fromStdString(condition));
    query.bindValue(":form", QString::fromStdString(c->getFormat()));
    query.bindValue(":stat", QString::fromStdString(status));
    query.bindValue(":size", 0);
    if(query.exec()){
        return true;
    }
    return false;
}

bool Library::removeItem(string& itemID){
    QSqlQuery query;
    query.prepare("SELECT * FROM catalogue WHERE title = :id");
    query.bindValue(":id", QString::fromStdString(itemID));
    query.exec();

    if(!query.next()){
        qDebug() << "ERROR: Item not found:" << query.lastError();
        return false;
    }
    itemID = query.value("itemID").toString().toStdString();
    query.prepare("DELETE FROM catalogue WHERE itemID = :id");
    query.bindValue(":id", QString::fromStdString(itemID));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}


