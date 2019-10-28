#include <string>

#include "calc.h"

// parse number
int num(std::string& s) {
    size_t sz;
    int num = std::stoi(s, &sz);
    s = s.substr(sz);

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    
    return num;
}

// calculate * and /
double mul_div(std::string& s) {
    double value = num(s);
    
    int divider;
    while (!s.empty()) {
        switch (s[0]) {
            case '*':
                s = s.substr(1);
                value *= num(s);
                break;
            case '/':
                s = s.substr(1);
                divider = num(s);
                if (divider == 0)  {
                    throw std::overflow_error("division by 0");
                }
                value /= divider;
                break;
            default:
                return value;
        }
    }
    return value;
}

// calculate + and -
double add_sub(std::string& s) {
    double value = mul_div(s);
    
    while (!s.empty()) {
        switch (s[0]) {
            case '+':
                s = s.substr(1);
                value += mul_div(s);
                break;
            case '-':
                s = s.substr(1);
                value -= mul_div(s);
                break;
            default:
                throw std::invalid_argument("unknown operation");
        }
    }
    return value;
}


// calculate equation
double calculate(const std::string & equation) {
    std::string s = equation;
    return add_sub(s);
};