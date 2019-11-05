#include "parser.hpp"

#include <sstream>

void Parser::parse(const std::string& str) const {
    on_start(str);
    std::istringstream stream(str);
    std::string token;
    while (!stream.eof()) {
        stream >> token;
        bool is_number = std::find_if(token.begin(), token.end(),
                                          [](char c) {return !std::isdigit(c);}
                                      ) == token.end();
        
        if (is_number) {
            int number = std::stoi(token);
            on_number(number);
        } else {
            on_string(token);
        }
    }
    on_end(str);
}
