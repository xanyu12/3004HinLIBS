#include "date.h"

Date::Date(int d, int m, int y){
    setDate(d, m, y);
}


int Date::getDay(){return day;}
int Date::getMonth(){return month;}
int Date::getYear(){return year;}

void Date::setDate(int d, int m, int y){
    year = ((y > 0)? y : 0);
    month = ((m > 0 && m <= 12)? m:0);
    day = ((d > 0 && d <= lastDayInMonth(m, y)) ? d : 0);
}

int Date::lastDayInMonth(int m, int y){
    switch(m){
    case 2:
        if(leapYear(y)){
            return 29;
        }else{
            return 28;
        }
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    default:
        return 30;
    }
}

bool Date::leapYear(int y){
    if(y % 400 == 0  || (y % 4 == 0 && y % 100 != 0)){
        return true;
    }else{
        return false;
    }
}

string Date::getMonthStr(int m){
    string months[] = {"January", "Februrary", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};
    return months[m-1];
}

bool Date::operator==(Date& other){
    if(year == other.year && month == other.month && day == other.day){
        return true;
     }else{
        return false;
    }
}

bool Date::operator<(Date& other){
    if(year < other.year){
        return true;
    }else if(year == other.year){
        if(month < other.month){
            return true;
        }else if(month == other.month){
            if(day < other.day){
                return true;
            }
        }
    }
    return false;
}
