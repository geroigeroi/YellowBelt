//
//  main.cpp
//  find_nearest_element
//
//  Created by Andre on 16/12/20.
//

#include <iostream>
#include <set>

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers, int border) {
    std::set<int>::const_iterator result;
    result = numbers.lower_bound(border);
    std::set<int>::const_iterator result2 = std::prev(result);
    if (*result - border == border - *result2) {
        return result2;
    }
    return result;
}
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел

int main() {
    std::set<int> numbers = {1, 4, 6};
      std::cout <<
          *FindNearestElement(numbers, 0) << " " <<
          *FindNearestElement(numbers, 3) << " " <<
          *FindNearestElement(numbers, 5) << " " <<
          *FindNearestElement(numbers, 6) << " " <<
          *FindNearestElement(numbers, 100) << std::endl;
          
      std::set<int> empty_set;
      
      std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
      return 0;
    return 0;
}
