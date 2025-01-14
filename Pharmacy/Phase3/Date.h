#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date {

private:

    int day_d;
    int month_d;
    int year_d;

public:

    Date(int day = 1, int month = 1, int year = 2000);
    Date(const Date& d);

    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void print_d() const;

    ~Date();

};
