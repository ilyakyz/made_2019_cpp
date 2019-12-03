#include <iostream>
#include "format.hpp"


template<typename... Args>
void assert_format_fail(const std::string& str, Args&&... args) {
    try {
        format(str, std::forward<Args>(args)...);
        assert(false);
    } catch (const std::runtime_error &) {
    }
}

int main(int argc, const char * argv[]) {
    assert(format("{1}+{1} = {0}", 2, "one") == "one+one = 2");
    assert(format("one+{0} = 3", 2) == "one+2 = 3");
    assert(format("{0}{1}{0}", 1, 2) == "121");
    assert(format("{2} {1} {0}", 1, "two", 3) == "3 two 1");
    assert(format("{0}{0}", "") == "");
    assert(format("one") == "one");
    assert_format_fail("{12a}", 1);
    assert_format_fail("{}");
    assert_format_fail("0} one", 1);
    assert_format_fail("one {0", 1);
    assert_format_fail("{{0}", 1);
    assert_format_fail("{0}}", 1);
    assert_format_fail("{1}+{1} = {0}", 2);
    std::cout << "OK\n";
    return 0;
}
