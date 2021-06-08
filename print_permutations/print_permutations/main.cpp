//
//  main.cpp
//  print_permutations
//
//  Created by Andre on 12/10/20.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    
    int digit;
    std::cin >> digit;
    // std::vector<int> v;
    std::vector<int> v(digit);
    std::iota(v.rbegin(), v.rend(), 1);
//    for (int i = digit; i > 0; --i) {
//        v.push_back(i);
//    }
    // std::reverse(v.begin(), v.end());
    do {
        for (auto i : v) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    } while (std::prev_permutation(v.begin(), v.end()));
    return 0;
}
