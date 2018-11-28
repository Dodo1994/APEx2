#include <iostream>
#include "interface.h"

int getYear(string Date) {
    int year = 0;
    int i = 0;
    while (Date[i] != '-') {
        year *= 10;
        year += Date[i] - '0';
        i++;
    }
    return year;
}

int getMonth(string Date) {
    int month = 0;
    int i = 0;
    while (Date[i] != '-') { i++; };
    i++;
    while (Date[i] != '-') {
        month *= 10;
        month += Date[i] - '0';
        i++;
    }
    return month;
}

int getDay(string date) {
    int day = 0;
    int i = 0;
    while (date[i] != '-') { i++; };
    i++;
    while (date[i] != '-') { i++; };
    i++;
    while (date[i] != '-') {
        day *= 10;
        day += date[i] - '0';
        i++;
    }
    return day;
}

bool isNum(char c) {
    return (c >= '0' && c <= '9');
}

Date::Date(string date) {
    if (date.length() != 10 && date.length() != 0) {
        cerr << "Illegal date argument" << endl;
    }
    string year, month, day;
    int i = 0;
    while (isNum(date[i])) {
        year += date[i];
        i++;
    }
    i++;
    while (isNum(date[i])) {
        month += date[i];
        i++;
    }
    i++;
    while (isNum(date[i])) {
        day += date[i];
        i++;
    }
    this->date = (year + "-" + month + "-" + day);
}

bool Date::operator<(const Date &d) const {
    int year1 = getYear(this->date);
    int month1 = getMonth(this->date);
    int day1 = getDay(this->date);

    int year2 = getYear(d.date);
    int month2 = getMonth(d.date);
    int day2 = getDay(d.date);

    if (year1 != year2) {
        return year1 > year2;
    }
    if (month1 != month2) {
        return month1 > month2;
    }
    if (day1 != day2) {
        return day1 > day2;
    }
    return true;
}

bool Date::operator>(const Date &d) const {
    return !(*this == d || *this < d);
}

bool Date::operator==(const Date &d) const {
    int year1 = getYear(this->date);
    int month1 = getMonth(this->date);
    int day1 = getDay(this->date);

    int year2 = getYear(d.date);
    int month2 = getMonth(d.date);
    int day2 = getDay(d.date);

    return (year1 == year2 && month1 == month2 && day1 == day2);
}