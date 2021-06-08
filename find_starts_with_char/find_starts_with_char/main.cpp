//
//  main.cpp
//  find_starts_with_char
//
//  Created by Andre on 17/12/20.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

bool comp(const std::string& lhs, const std::string& rhs) {
    int cmp = std::strncmp(lhs.data(), rhs.data(), 1);
    if (cmp < 0) {  // Первая буква следующего слова больше нашей буквы
        return true;
    }
    return false;
}

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    std::pair<RandomIt, RandomIt> result;
    std::string prefix_str(1, prefix);
    auto lb = std::lower_bound(range_begin, range_end, prefix_str);
    auto ub = std::upper_bound(lb, range_end, prefix_str, comp);
    result = std::make_pair(lb, ub);
    return result;
}

int main() {
    const std::vector<std::string> sorted_strings = {"moscow", "murmansk", "vologda"};
    
    const auto m_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    const auto p_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    std::cout << (p_result.first - begin(sorted_strings)) << " " << (p_result.second - begin(sorted_strings)) << std::endl;
    
    const auto z_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    std::cout << (z_result.first - begin(sorted_strings)) << " " << (z_result.second - begin(sorted_strings)) << std::endl;
    
    return 0;
}
