//
//  main.cpp
//  build_expression
//
//  Created by Andre on 17/12/20.
//

#include <iostream>
#include <string>
#include <sstream>

void BuildExpression(std::string& exp, const std::string& cmd) {
    exp = '(' + exp + ')';
    if (cmd[2] == '-') {
        exp = exp + ' ' + cmd[0] + ' ' + cmd[2] + cmd[3];
    } else {
        exp = exp + ' ' + cmd[0] + ' ' + cmd[2];
    }
}

int main() {
    int startDigit, quantityOper;
    std::cin >> startDigit;
    std::cin >> quantityOper;
    if (!quantityOper) {
        std::cout << startDigit << '\n';
        return 0;
    }
    std::cin.ignore();
    std::string result = std::to_string(startDigit);
    int i = 0;
    while (i < quantityOper) {
        std::string command;
        std::getline(std::cin, command);
        BuildExpression(result, command);
        ++i;
    }
    std::cout << result << '\n';
    return 0;
}
