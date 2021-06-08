//
//  main.cpp
//  element_reference
//
//  Created by  Mister on 01.12.2020.
//

#include <iostream>
#include <map>
#include <stdexcept>

template <typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value>& map_for_search, const Key& key_to_search) {
    if (map_for_search.count(key_to_search)) {  // Если найдено
        Value& result = map_for_search.at(key_to_search);
        return result;
    } else {
        throw std::runtime_error("Runtime error");
    }
}

int main() {
    
    std::map<int, std::string> m = {{0, "value"}};
    std::string& item = GetRefStrict(m, 1);
    item = "newvalue";
    std::cout << m[0] << std::endl; // выведет newvalue
    
    return 0;
}
