#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

class Date {
public:
    Date(){}
    Date(const int& y, const int& m, const int& d) : year_(y), month_(m), day_(d) {}
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    void SetYear(int new_year);
    void SetMonth(int new_month);
    void SetDay(int new_day);

private:
    int year_;
    int month_;
    int day_;
};

bool operator!=(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator<(const Date& lhs, const Date& rhs);

bool operator>(const Date& lhs, const Date& rhs);

std::ostream& operator<<(std::ostream& stream, const Date& date);

Date ParseDate(std::istream& is);

std::string ParseEvent(std::istringstream& parseNewEvent);
