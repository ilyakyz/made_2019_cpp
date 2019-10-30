#ifndef allocator_hpp
#define allocator_hpp

#include <stdio.h>

class Allocator {
private:
    char* memory;
    size_t max_size;
    size_t offset;
public:
    Allocator(size_t maxSize);
    char* alloc(size_t size);
    void free();
    ~Allocator();
};

#endif /* allocator_hpp */
