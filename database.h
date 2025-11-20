#ifndef DATABASE_H
#define DATABASE_H
#include <QtDebug>

#include "catalogueItem.h"

class Database{
public:

    Database();

    bool handleCheckOut(string& s, string& t);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
