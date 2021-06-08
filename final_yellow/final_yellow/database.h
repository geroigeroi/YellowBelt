#pragma once
#include "date.h"
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>

std::ostream& operator<<(std::ostream& stream, const std::pair<Date, std::string> oLast);  // Возможно надо будет поменять на ostringstream

bool operator!=(const std::pair<Date, std::string>& lhs, const std::pair<Date, std::string>& rhs);

class Database {
public:
    void Add(const Date& date, const std::string& event);
    void Print(std::ostream &os) const;
    std::vector<std::pair<Date, std::string>> FindIf(const std::function<bool(const Date&, const std::string&)> pred) const;
    int RemoveIf(const std::function<bool(const Date&, const std::string&)> pred);
    std::pair<Date, std::string> Last(const Date& date) const;
    
private:
    std::map<Date, std::set<std::string>, std::greater<Date>> databaseEntryUnique;
    std::map<Date, std::vector<std::string>> databaseEntryOrdered;
};
