//
//  main.cpp
//  merge_sort_div2
//
//  Created by Andre on 12/12/20.
//

#include <iostream>
#include <vector>
#include <algorithm>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
    size_t middle = elements.size() / 2;
    auto middle_it = elements.begin() + middle;
    MergeSort(elements.begin(), middle_it);
    MergeSort(middle_it, elements.end());
    std::merge(elements.begin(), middle_it, middle_it, elements.end(), range_begin);
}

int main() {
      std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
      MergeSort(begin(v), end(v));
      for (int x : v) {
        std::cout << x << " ";
      }
      std::cout << std::endl;
    return 0;
}
