#include <iostream>
#include "hello.h"

Hello::Hello() {
    this->status = 0;
    std::cout << "constructor" << std::endl;
}

Hello::~Hello() {
    std::cout << "destructor" << std::endl;
}

int Hello::printHello() {
    std::cout << "Called from the server!" << std::endl;
    return 0;
}


