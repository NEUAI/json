#include "json/json.h"

#include <iostream>

int main() {
    try {
        json::object obj;
        std::cin >> obj;
        std::cout << obj << std::endl;
    } catch (std::exception &) {
        std::cerr << "json: An exception was caught." << std::endl;
    }
    return 0;
}
