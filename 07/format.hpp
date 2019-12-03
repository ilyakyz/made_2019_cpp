#ifndef format_hpp
#define format_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>


void args_to_str(std::vector<std::string>& result);

template<typename T, typename... Args>
void args_to_str(std::vector<std::string>& result, T&& t, Args&&... args) {
    std::ostringstream stream;
    stream << t;
    result.push_back(stream.str());
    args_to_str(result, std::forward<Args>(args)...);
}

template<typename... Args>
std::string format(const std::string& str, Args&&... args) {
    std::vector<std::string> args_str;
    args_to_str(args_str, std::forward<Args>(args)...);
    
    std::string result;
    
    bool open = false;
    size_t prev_idx = 0;
    std::size_t idx = str.find_first_of("{}");
    while (idx != std::string::npos) {
        if (str[idx] == '{') {
            if (open) throw std::runtime_error("unexpected { on char " + std::to_string(idx));
            if (prev_idx < idx)
                result += str.substr(prev_idx, idx-prev_idx);
        } else {
            if (!open) throw std::runtime_error("unexpected } on char " + std::to_string(idx));
            int substitute;
            try {
                substitute = stoi(str.substr(prev_idx, idx-prev_idx));
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error(e.what());
            }
            if (substitute >= args_str.size())
                throw std::runtime_error("too few args for num " + std::to_string(substitute));
            result += args_str[substitute];
        }
        prev_idx = idx + 1;
        open = !open;
        idx = str.find_first_of("{}", prev_idx);
    }
    if (open) throw std::runtime_error("no closing }");
    if (prev_idx + 1 < str.size())
        result += str.substr(prev_idx, idx-prev_idx);
    
    return result;
}

#endif /* format_hpp */
