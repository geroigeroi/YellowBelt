//
//  main.cpp
//  blocks_weight
//
//  Created by  Mister on 23.11.2020.
//

#include <iostream>
#include <limits>

int main() {
    unsigned quantityOfBlocks;
    unsigned density;
    unsigned w, h, d;
    uint64_t mass = 0;
    std::cin >> quantityOfBlocks >> density;
    for (size_t i = 0; i < quantityOfBlocks; ++i) {
        std::cin >> w >> h >> d;
        uint64_t volume = static_cast<int64_t>(w * h) * d;
        mass += volume;
    }
    mass *= density;
    std::cout << mass;
    return 0;
}
