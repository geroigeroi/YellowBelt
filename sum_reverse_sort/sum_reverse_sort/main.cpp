//
//  main.cpp
//  sum_reverse_sort
//
//  Created by Andre on 12/9/20.
//

#include <iostream>
#include "sum_reverse_sort.h"


int main() {
    std::cout << Reverse("abcdef") << "\n";
    std::vector<int> nums = {12, 5, 10, 1, 0, 12, 6};
    Sort(nums);
    for (const auto& i : nums) {
        std::cout << i << " ";
    }
    
    return 0;
}
