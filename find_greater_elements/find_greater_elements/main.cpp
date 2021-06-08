//
//  main.cpp
//  find_greater_elements
//
//  Created by Andre on 12/10/20.
//

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
    std::vector<T> result;
    auto pos = std::find_if(elements.begin(), elements.end(), [&](T x) {
        return x > border;
    });
    while (pos != elements.end()) {
        result.push_back(*pos);
        ++pos;
    }
    return result;
}

int main() {
    for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) {
        std::cout << x << " ";
      }
      std::cout << std::endl;
      
      std::string to_find = "Python";
      std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;
      return 0;
    return 0;
}
