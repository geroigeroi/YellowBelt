//
//  main.cpp
//  merge_sort_div3
//
//  Created by Andre on 12/16/20.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
    size_t quan = elements.size() / 3;  // 27 : 3 = 9
    auto firstOneThird_End = elements.begin() + elements.size() / 3;
    auto secondOneThird_Begin = firstOneThird_End;
    auto secondOneThird_End = elements.begin() + elements.size() * 2 / 3;
    auto thirdOneThird_Begin = secondOneThird_End;
    MergeSort(elements.begin(), firstOneThird_End);
    MergeSort(secondOneThird_Begin, secondOneThird_End);
    MergeSort(thirdOneThird_Begin, elements.end());
    std::vector<typename RandomIt::value_type> tempV;
    std::merge(elements.begin(), firstOneThird_End, secondOneThird_Begin, secondOneThird_End, std::back_inserter(tempV));
    std::merge(tempV.begin(), tempV.end(), thirdOneThird_Begin, elements.end(), range_begin);
}

int main() {
    std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
      MergeSort(begin(v), end(v));
      for (int x : v) {
        std::cout << x << " ";
      }
      std::cout << std::endl;
      return 0;
    return 0;
}
