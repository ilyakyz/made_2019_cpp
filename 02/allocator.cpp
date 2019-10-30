#include "allocator.hpp"
#include <cstdlib>
#include <stdexcept>
#include <string>

Allocator::Allocator(size_t maxSize): max_size(maxSize), offset(0) {
    memory = static_cast<char*>(std::malloc(maxSize));
};

Allocator::~Allocator() {
    std::free(memory);
};

char* Allocator::alloc(size_t size) {
    if (offset + size > max_size) {
        throw std::overflow_error("only " + std::to_string(max_size - offset) + " bytes are free");
    }
    char* result = memory + offset;
    offset += size;
    return result;
};

void Allocator::free() {
    offset = 0;
}
