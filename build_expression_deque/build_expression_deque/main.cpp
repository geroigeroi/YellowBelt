//
//  main.cpp
//  build_expression_deque
//
//  Created by Andre on 23/12/20.
//

#include <iostream>
#include <deque>
#include <string>

int main() {
    int startDigit;
    int quantityOper;
    std::cin >> startDigit;
    std::cin >> quantityOper;
    if (!quantityOper) {
        std::cout << startDigit << std::endl;
        return 0;
    }
    std::deque<std::string> expression;
    std::string dgt = std::to_string(startDigit);
    expression.push_front(dgt);
    std::cin.ignore();
    int i = 0;
    while (i < quantityOper) {
        std::string command;
        std::getline(std::cin, command);
        expression.push_front("(");
        expression.push_back(")");
        expression.push_back(" ");
        expression.push_back(command);
        ++i;
    }
    for (size_t i = 0; i < expression.size(); ++i) {
        std::cout << expression[i];
    }
    // std::cout << std::endl;
    return 0;
}
