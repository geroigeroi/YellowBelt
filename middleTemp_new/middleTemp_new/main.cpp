//
//  main.cpp
//  middleTemp_new
//
//  Created by  Mister on 23.11.2020.
//

#include <iostream>
#include <cstddef>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    unsigned N;  // Количество дней
    std::cin >> N;
    std::vector<int> temperature(N);
    int64_t sum = 0;
    int average;
    
    /* Ввод значений температуры */
    for (auto& s : temperature) {
        std::cin >> s;
    }
    /* Вычисляем среднее арифметическое температуры */
    for (auto s : temperature) {
        sum = sum + s;
    }
    average = int(sum / N);
    std::cout << count_if(std::begin(temperature), std::end(temperature), [average](int x) {
        if (x > average) {
            return true;
        }
        return false;
    });
    std::cout << std::endl;
    
    for (size_t i = 0; i < temperature.size(); ++i) {
        if (temperature[i] > average) {
            std::cout << i << " ";
        }
    }
    
    return 0;
}
