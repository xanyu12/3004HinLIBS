#ifndef DATE_H
#define DATE_H

class Date{
public:
    Date();

    int getYear();
    int getMonth();
    int getDay();

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);

    void print();

    bool operator==(Date& other);
    bool operator<(Date& other);
private:
    int year;
    int month;
    int day;
};

#endif // DATE_H
