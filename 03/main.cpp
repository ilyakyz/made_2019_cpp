#include <iostream>
#include <vector>

#include "parser.hpp"

enum Action {
    STRING,
    NUMBER,
    START,
    END,
};

struct Response {
    Action action;
    std::string str;
    int number;
};

int main(int argc, const char * argv[]) {
    Parser parser;
    
    std::vector<Response> result;
    parser.set_on_start([&result](const std::string& s){result.push_back({START, s, 0});});
    parser.set_on_end([&result](const std::string& s){result.push_back({END, s, 0});});
    parser.set_on_string([&result](const std::string& s){result.push_back({STRING, s, 0});});
    parser.set_on_number([&result](int n){result.push_back({NUMBER, "", n});});
    
    parser.parse("2 + 3");
    assert(result.size() == 5);
    assert(result[0].action == START);
    assert(result[1].action == NUMBER);
    assert(result[1].number == 2);
    assert(result[2].action == STRING);
    assert(result[2].str == "+");
    assert(result[3].action == NUMBER);
    assert(result[3].number == 3);
    assert(result[4].action == END);
    std::cout << "OK\n";
    return 0;
}
