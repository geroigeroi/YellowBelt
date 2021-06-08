//
//  sum_reverse_sort.cpp
//  sum_reverse_sort
//
//  Created by Andre on 12/9/20.
//
#include <string>
#include <vector>
#include <algorithm>
#include "sum_reverse_sort.h"

int Sum(int x, int y) {
    return x + y;
}

std::string Reverse(std::string s) {
    std::string result;
    std::reverse(s.begin(), s.end());
    return s;
}

void Sort(std::vector<int>& nums) {
//    size_t sz = nums.size();
//    while (sz != 0) {
//        for (size_t i = 0; i < sz - 1; ++i) {
//            if (nums[i] > nums[i + 1]) {
//                int tmp = nums[i];
//                nums[i] = nums[i + 1];
//                nums[i + 1] = tmp;
//            }
//        }
//        --sz;
//    }
    std::sort(nums.begin(), nums.end());
}
