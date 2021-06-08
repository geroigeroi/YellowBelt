//
//  main.cpp
//  print_vector_part
//
//  Created by Andre on 12/9/20.
//

#include <iostream>
#include <vector>
#include <algorithm>

void PrintVectorPart(const std::vector<int>& numbers) {
    auto itFirstNeg = std::find_if(numbers.begin(), numbers.end(), [](int x) {
        if (x < 0) {
            return true;
        }
        return false;
    });
    while (itFirstNeg != numbers.begin()) {
        --itFirstNeg;
        std::cout << *itFirstNeg << " ";
    }
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    std::cout << std::endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    std::cout << std::endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    std::cout << std::endl;
    return 0;
}
