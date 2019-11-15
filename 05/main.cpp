#include <iostream>
#include <sstream>

#include "serializer.h"

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b, c);
    }
};

struct BigData {
    Data data;
    uint64_t x;
    
    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(data, x);
    }
};


void assert_fail_load(const std::string& str) {
    BigData data;
    std::istringstream istream(str);
    Deserializer deserializer(istream);
    Error error = deserializer.load(data);
    assert(error == Error::CorruptedArchive);
}

int main(int argc, const char * argv[]) {
    BigData data {{1, true, 2}, 3};
    
    std::stringstream stream;
    Serializer serializer(stream);
    Error error = serializer.save(data);
    assert(error == Error::NoError);

    BigData data2;
    Deserializer deserializer(stream);
    error = deserializer.load(data2);
    assert(error == Error::NoError);
    assert(data2.data.a == 1);
    assert(data2.data.b == true);
    assert(data2.data.c == 2);
    assert(data2.x == 3);
   
    assert_fail_load("-1 true 3 4");
    assert_fail_load("1 1 2 3");
    assert_fail_load("1 true 2");
    assert_fail_load("1 true 2 3 4");
    
    std::cout << "OK\n";
    return 0;
}
