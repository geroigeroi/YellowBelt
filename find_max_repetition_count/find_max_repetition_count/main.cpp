//
//  main.cpp
//  find_max_repetition_count
//
//  Created by  Mister on 23.11.2020.
//

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>

enum class Lang {
  DE, FR, IT
};

struct Region {
  std::string std_name;
  std::string parent_std_name;
  std::map<Lang, std::string> names;
  int64_t population;
};

bool operator==(const Region& lhs, const Region& rhs) {
    if (lhs.population != rhs.population) {
        return false;
    }
    if (lhs.std_name != rhs.std_name) {
        return false;
    }
    if (lhs.parent_std_name != rhs.parent_std_name) {
        return false;
    }
    if (lhs.names != rhs.names) {
        return false;
    }
    return true;
}

bool operator<(const Region& lhs, const Region& rhs) {
    return std::tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) < std::tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const std::vector<Region>& regions) {
    int result = 0;
    if (!regions.size()) {
        return result;
    }
    std::set<Region> regions_set(regions.begin(), regions.end());
    std::vector<size_t> quantityOfEach(regions_set.size());
    for (const auto& i : regions_set) {
        quantityOfEach.push_back(std::count(regions.begin(), regions.end(), i));
    }
    result = (int)*max_element(quantityOfEach.begin(), quantityOfEach.end());
    return result;
}

int main() {
    
    std::cout << FindMaxRepetitionCount({
        {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        },
    }) << std::endl;
    
    std::cout << FindMaxRepetitionCount({
        {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Toulouse",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            31
        },
    }) << std::endl;
    
    
    return 0;
}
