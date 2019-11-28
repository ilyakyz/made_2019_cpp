#include <iostream>
#include <sstream>
#include "big_int.hpp"

int main(int argc, const char * argv[]) {
    {
        BigInt b1(123);
        BigInt b2 = b1;
        BigInt b3(1234);
        BigInt b4(-1234567891);
        assert(b1 == b2);
        assert(b1 != b4);
        assert(b3 != b4);
        assert(b1 < b3);
        assert(b1 < 11111);
        assert(b3 < 3412);
        assert(b1 <= b3);
        assert(b1 <= b1);
        assert(b1 > b4);
        assert(-b3 > -3412);
        assert(b1 >= b1);
        assert(!(b1 >= b3));
        assert(b2 == BigInt(123));
        assert(b2 == 123);
        assert(-1234567891 == b4);
        b3 = b3;
        assert(b3 == 1234);
        b3 = b1;
        assert(b3 == 123);
    }
    {
        BigInt b1(87);
        BigInt b2(34);
        BigInt b3(123);
        assert(-b3 == -123);
        assert(-(-b3) == 123);
        assert(-BigInt(123) == -123);
        assert(-BigInt(0) == 0);
        assert(b1 + b2 == 121);
        assert(b1 + b3 == 210);
        assert(b3 + -33 == 90);
        assert(b3 - 33 == 90);
        assert(-b3 + 33 == -90);
        assert(-b3 - -33 == -90);
        assert(-b3 -33 == -156);
        assert(-b3 + b3 == 0);
        assert(b3 - 12345 == -12222);
        assert(1 + b1 + 123 == 211);
    }
    {
        std::ostringstream ss;
        ss << BigInt(123);
        assert(ss.str() == "123");
        ss.clear();
    }
    {
        std::ostringstream ss;
        ss << BigInt(-10003);
        assert(ss.str() == "-10003");
    }
    {
        std::ostringstream ss;
        ss << BigInt(0);
        assert(ss.str() == "0");
        ss.clear();
    }
    
    std::cout << "OK\n";
    return 0;
}
