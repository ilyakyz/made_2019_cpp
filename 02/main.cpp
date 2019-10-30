#include <iostream>
#include "allocator.hpp"

int main(int argc, const char * argv[]) {
    Allocator allocator(8);
    char* c1 = allocator.alloc(5);
    allocator.free();
    c1 = allocator.alloc(5);
    char* c2 = allocator.alloc(3);
    assert(c2 - c1 == 5);
    bool failed = false;
    try {
        c1 = allocator.alloc(1);
    } catch(const std::overflow_error&) {
        failed = true;
    }
    assert(failed);
    std::cout << "OK\n";
    return 0;
}
