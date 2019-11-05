#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include <functional>

typedef std::function<void(const std::string&)> str_func;
typedef std::function<void(int)> int_func;

class Parser {
public:
    void parse(const std::string& str) const;
    
    void set_on_string(str_func on_string) {
        this->on_string = on_string;
    }
    
    void set_on_number(int_func on_number) {
        this->on_number = on_number;
    }
    
    void set_on_start(str_func on_start) {
        this->on_start = on_start;
    }
    
    void set_on_end(str_func on_end) {
        this->on_end = on_end;
    }
    
private:
    str_func on_string = [](const std::string&){};
    int_func on_number = [](int){};
    str_func on_start = [](const std::string&){};
    str_func on_end = [](const std::string&){};
};

#endif /* parser_hpp */
