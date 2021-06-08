#include "date.h"


int Date::GetYear() const {
    return year_;
}
int Date::GetMonth() const {
    return month_;
}
int Date::GetDay() const {
    return day_;
}
void Date::SetYear(int new_year) {
    year_ = new_year;
}
void Date::SetMonth(int new_month) {
    month_ = new_month;
}
void Date::SetDay(int new_day) {
    day_ = new_day;
}

bool operator!=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() == rhs.GetDay()) {
                return false;
            }
        }
    }
    return true;
}

bool operator==(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() == rhs.GetDay()) {
                return true;
            }
        }
    }
    return false;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() < rhs.GetDay()) {
                return true;
            } else {
                return false;
            }
        } else if (lhs.GetMonth() < rhs.GetMonth()) {
            return true;
        } else {
            return false;
        }
    } else if (lhs.GetYear() < rhs.GetYear()) {
        return true;
    } else {
        return false;
    }
}

bool operator>(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() > rhs.GetDay()) {
                return true;
            } else {
                return false;
            }
        } else if (lhs.GetMonth() > rhs.GetMonth()) {
            return true;
        } else {
            return false;
        }
    } else if (lhs.GetYear() > rhs.GetYear()) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << std::setfill('0');
    stream << std::setw(4) << date.GetYear() << "-"
           << std::setw(2) << date.GetMonth() << "-"
           << std::setw(2) << date.GetDay();
    return stream;
}

Date ParseDate(std::istream& is) {
    Date result;
    int year, month, day;
    is >> year;
    is.ignore();
    is >> month;
    is.ignore();
    is >> day;
    result.SetYear(year);
    result.SetMonth(month);
    result.SetDay(day);
    return result;
}

std::string ParseEvent(std::istringstream& inpStr_WithDateAndEvent) {
    inpStr_WithDateAndEvent.ignore();
    std::string event;
    std::getline(inpStr_WithDateAndEvent, event);
    event = event.substr(event.find_first_not_of(' '));
    return event;
}
