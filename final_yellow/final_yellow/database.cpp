#include "database.h"

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

std::ostream& operator<<(std::ostream& stream, const std::pair<Date, std::string> oLast) {
    stream << oLast.first << " " << oLast.second;
    return stream;
}

bool operator!=(const std::pair<Date, std::string>& lhs, const std::pair<Date, std::string>& rhs) {
    if (lhs.first > rhs.first || lhs.first < rhs.first) {
        return true;
    } else if (lhs.second != rhs.second) {
        return true;
    }
    return false;
}

void Database::Add(const Date& date, const std::string& event) {
    if (databaseEntryUnique[date].insert(event).second) {  // В эту дату данного события нет (и оно уже добавилось)
        databaseEntryOrdered[date].push_back(event);  // Добавил событие в конец
    }
}

std::pair<Date, std::string> Database::Last(const Date& date) const {
    auto it = databaseEntryUnique.lower_bound(date);
    if (it == databaseEntryUnique.end()) {  // Даты меньше введённой — нет
        throw std::invalid_argument("");
    } else {
        const Date dateResult = (*it).first;
        const std::string eventResult = databaseEntryOrdered.at(dateResult).back();
        std::pair<Date, std::string> result = std::make_pair(dateResult, eventResult);
        return result;
    }
}

void Database::Print(std::ostream& os) const {
    for (const auto& dates : databaseEntryOrdered) {
        for (const auto& events : dates.second) {
            os << dates.first << " " << events << std::endl;
        }
    }
}

int Database::RemoveIf(const std::function<bool(const Date&, const std::string&)> pred) {
    // databaseEntryOrdered — мапа из Date в вектор событий (стрингов). События уникальны и лежат в порядке добавления
    // databaseEntryUnique  - мапа из Date в сет событий (стрингов). События уникальны и лежат по возрастанию
    int result = 0;
    for (auto it = databaseEntryOrdered.begin(); it != databaseEntryOrdered.end();) {
        const Date date = it->first;
        auto bound = std::stable_partition(it->second.begin(), it->second.end(), [date, pred](const std::string& event) {
            return !pred(date, event);
        });
        for (auto bound_for_set = bound; bound_for_set != it->second.end(); ++bound_for_set) {
            databaseEntryUnique.at(date).erase(*bound_for_set);
            ++result;
        }
        it->second.erase(bound, it->second.end());
        if (it->second.empty()) {
            databaseEntryUnique.erase(date);
            it = databaseEntryOrdered.erase(it);
        } else {
            ++it;
        }
    }
    return result;
}

std::vector<std::pair<Date, std::string>> Database::FindIf(const std::function<bool(const Date&, const std::string&)> pred) const {
    std::vector<std::pair<Date, std::string>> result;
    for (const auto& [date, vec_Events] : databaseEntryOrdered) {
        for (const auto& event : vec_Events) {
            if (pred(date, event)) {
                result.push_back(std::make_pair(date, event));
            }
        }
    }
    return result;
}
