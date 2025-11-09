#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

#include <ctime>

class Date{
public:
    Date(int=0, int=0, int=2000);

    void getCurrentDate();

    int getYear();
    int getMonth();
    int getDay();

    long toDays();

    void setDate(int, int, int);

    void print();

    bool operator==(Date& other);
    bool operator<(Date& other);
    int operator-(Date& other);

private:
    int year;
    int month;
    int day;
    int lastDayInMonth(int, int);
    bool leapYear(int);
    string getMonthStr(int);
};

#endif // DATE_H
