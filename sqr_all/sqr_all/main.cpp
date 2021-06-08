//
//  main.cpp
//  sqr_all
//
//  Created by  Mister on 29.11.2020.
//

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <utility>

template <typename Key, typename Value> std::map<Key, Value> Sqr(std::map<Key, Value> mp);
template <typename T> std::vector<T> Sqr(std::vector<T> vec);
template <typename First, typename Second> std::pair<First, Second> Sqr(std::pair<First, Second> p);
template <typename T> T Sqr(const T& x);

template <typename Key, typename Value>
std::map<Key, Value> Sqr(std::map<Key, Value> mp) {
    std::map<Key, Value> result_Map;
    for (auto i: mp) {
        result_Map[i.first] = Sqr(i.second);
    }
    return result_Map;
}

template <typename T>
std::vector<T> Sqr(std::vector<T> vec) {
    std::vector<T> result_Vec;
    for (auto i : vec) {
        auto tmp = Sqr(i);
        result_Vec.push_back(tmp);
    }
    return result_Vec;
}

template <typename First, typename Second>
std::pair<First, Second> Sqr(std::pair<First, Second> p) {
    std::pair<First, Second> result_pair;
    result_pair = std::make_pair(Sqr(p.first), Sqr(p.second));
    return result_pair;
}

template <class T>
T Sqr(const T& x) {
    return x * x;
}


    

int main() {
    std::vector<int> v = {1, 2, 3};
    std::cout << "vector:";
    for (int x : Sqr(v)) {
      std::cout << ' ' << x;
    }
    std::cout << std::endl;
    
    std::map<int, std::pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
    };
    std::cout << "map of pairs:" << std::endl;
    for (const auto& x : Sqr(map_of_pairs)) {
      std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
    }
    
//    std::vector<std::map<int, int>> vec_map = { {2, 3}, {3, 4}, {5, 6} };
//    std::cout << "vector of maps:" << std::endl;
//    for (const auto& x : Sqr(vec_map)) {
//        for (const auto& x1 : x) {
//            std::cout << x1.first << '=' << x1.second << '\n';
//        }
//    }
    
    return 0;
}
