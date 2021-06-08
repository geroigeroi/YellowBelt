//
//  main.cpp
//  split_into_words
//
//  Created by Andre on 12/10/20.
//

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::string> SplitIntoWords(const std::string& s) {
    std::vector<std::string> result;
    size_t lenghtWord = 0;
    for (auto it = s.begin(); it < s.end(); it += lenghtWord) {
        std::string findedStr(it, std::find(it, s.end(), ' '));
        result.push_back(findedStr);
        lenghtWord = findedStr.length();
        ++lenghtWord;
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    std::string s = "C++ Cpp Java Python";

      std::vector<std::string> words = SplitIntoWords(s);
      std::cout << words.size() << " ";
      for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
          std::cout << "/";
        }
        std::cout << *it;
      }
      std::cout << std::endl;
      
      return 0;
}
