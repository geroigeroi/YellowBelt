//
//  main.cpp
//  inheritance
//
//  Created by Andre on 24/12/20.
//

#include <iostream>

class Animal {
public:
    Animal(const std::string& nm) : Name(nm) {
        
    }

    const std::string Name;
};


class Dog : public Animal {
public:
    Dog(const std::string& nm) : Animal(nm) {
        
    }

    void Bark() {
        std::cout << Name << " barks: woof!" << std::endl;
    }
};

int main() {
    Dog d("Barbos");
    d.Bark();
    
    return 0;
}
