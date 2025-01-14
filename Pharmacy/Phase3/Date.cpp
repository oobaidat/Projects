#include "Date.h"
#include <iostream>
#include <string>
using namespace std;

// defaulted constructor, initializes a date object given day, month and year, otherwise gives default values.
Date::Date(int day, int month, int year) {

    setDay(day);
    setMonth(month);
    setYear(year);

}
// copy constructor, copies a date object.
Date::Date(const Date& d) {

    day_d = d.day_d;
    month_d = d.month_d;
    year_d = d.year_d;

}
// setters with validations. if it isn't satisfied set value to default
void Date::setDay(int day) {

    if (day < 1 || day > 31) {
        cout << "ERORR set day to 1" << endl;
        day_d = 1;
    }
    else {
        day_d = day;
    }

}

void Date::setMonth(int month) {

    if (month < 1 || month > 12) {
        cout << "ERORR set month to 1" << endl;
        month_d = 1;
    }
    else {
        month_d = month;
    }

}

void Date::setYear(int year) {

    if (year < 1900 || year > 2100) {
        cout << "ERORR set year to 2000" << endl;
        year_d = 2000;
    }
    else {
        year_d = year;
    }

}
//getter functions for day, month, and year.
int Date::getDay() const { return day_d; }
int Date::getMonth() const { return month_d; }
int Date::getYear() const { return year_d; }

//print function that prints the data in form day/month/year
void Date::print_d() const {
    cout << day_d << "/" << month_d << "/" << year_d << endl;
}
// destructor
Date::~Date() {}
