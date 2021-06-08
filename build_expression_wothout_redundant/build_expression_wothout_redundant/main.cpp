//
//  main.cpp
//  build_expression_wothout_redundant
//
//  Created by Andre on 23/12/20.
//

#include <iostream>
#include <deque>
#include <string>

void AddParenthesis(std::deque<std::string>& exp) {
    exp.push_front("(");
    exp.push_back(")");
    //exp.push_back(" ");
}

bool isAddParenthesis(const char prevOper, const char currOper) {
    if (currOper == '*' || currOper == '/') {
        if (prevOper == '+' || prevOper == '-') {
            return true;
        }
    }
    return false;
}

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
    bool isFirst = true;
    char prevOper;
    while (i < quantityOper) {
        std::string command;
        std::getline(std::cin, command);
        if (!isFirst) {
            char currOper = command[0];
            if (isAddParenthesis(prevOper, currOper)) {
                AddParenthesis(expression);
            }
        }
        expression.push_back(" ");
        expression.push_back(command);
        prevOper = command[0];
        isFirst = false;
        ++i;
    }
    for (size_t i = 0; i < expression.size(); ++i) {
        std::cout << expression[i];
    }
    // std::cout << std::endl;
    return 0;
}
