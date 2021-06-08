//
//  main.cpp
//  find_starts_with_string
//
//  Created by Andre on 17/12/20.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const std::string& prefix) {
    std::pair<RandomIt, RandomIt> result;
    auto lb = std::lower_bound(range_begin, range_end, prefix);
    auto ub = std::upper_bound(lb, range_end, prefix, [&](const std::string lhs, const std::string rhs){
        int cmp = std::strncmp(lhs.data(), rhs.data(), prefix.size());
        if (cmp < 0) {
            return true;
        }
        return false;
    });
    result = std::make_pair(lb, ub);
    return result;
}

int main() {
    const std::vector<std::string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
      
      const auto mo_result =
          FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
      for (auto it = mo_result.first; it != mo_result.second; ++it) {
        std::cout << *it << " ";
      }
      std::cout << std::endl;
      
      const auto mt_result =
          FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
      std::cout << (mt_result.first - begin(sorted_strings)) << " " <<
          (mt_result.second - begin(sorted_strings)) << std::endl;
      
      const auto na_result =
          FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
      std::cout << (na_result.first - begin(sorted_strings)) << " " <<
          (na_result.second - begin(sorted_strings)) << std::endl;
      
      return 0;
}
