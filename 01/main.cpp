#include <iostream>

#include "calc.h"

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        std::cerr << "wrong number of args" << std::endl;
        return -1;
    }
    try {
        std::cout << calculate(argv[1]) << std::endl;
    } catch (const std::invalid_argument&) {
        std::cerr << "unable to parse equation" << std::endl;
        return -1;
    } catch (const std::overflow_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
