#include "database.h"
#include "defs.h"

Database::Database(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/student/3004HinLIBS/PRAChinlibs.db");

    if(!db.open()){
        cout << "CANNOT CONNECT" << endl;
        return;
    }

    cout << "CONNECTED" << endl;
}


void Database::
