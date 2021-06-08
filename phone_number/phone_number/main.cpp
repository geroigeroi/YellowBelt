//
//  main.cpp
//  phone_number
//
//  Created by Andre on 12/9/20.
//

#include <iostream>
#include "phone_number.h"

int main() {
    PhoneNumber ph("1-2-33");
    try {
        std::cout << ph.GetInternationalNumber();
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
    return 0;
}
