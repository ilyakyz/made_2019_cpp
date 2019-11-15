#ifndef serializer_h
#define serializer_h

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out): out_(out) {
    }

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args) {
        return process(args...);
    }
    
private:
    template <class ValT, class... ArgsT>
    Error process(ValT& val, ArgsT&... args) {
        Error error = process(val);
        if (error != Error::NoError) {
            return error;
        }
        out_ << Separator;
        return process(args...);
    }
    
    template <class ValT>
    Error process(ValT& val) {
        return val.serialize(*this);
    }

    Error process(bool val) {
        out_ << (val ? "true" : "false");
        return Error::NoError;
    }
    
    Error process(uint64_t val) {
        out_ << val;
        return Error::NoError;
    }
    
    std::ostream& out_;
};


class Deserializer {
public:
    explicit Deserializer(std::istream& in): in_(in) {
    }

    template <class T>
    Error load(T& object) {
        Error result = object.serialize(*this);
        if (!in_.eof()) return Error::CorruptedArchive;
        return result;
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args) {
        return process(args...);
    }
    
private:
    template <class ValT, class... ArgsT>
    Error process(ValT& val, ArgsT&... args) {
        Error error = process(val);
        if (error != Error::NoError) {
            return error;
        }
        return process(args...);
    }
    
    template <class ValT>
    Error process(ValT& val) {
        return val.serialize(*this);
    }

    Error process(bool& val) {
        std::string text;
        in_ >> text;

        if (text == "true")
            val = true;
        else if (text == "false")
            val = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }
    
    Error process(uint64_t& val) {
        std::string text;
        in_ >> text;
        
        if (text.empty() ||
            std::find_if(text.begin(), text.end(), [](char c) {return !std::isdigit(c);}) != text.end())
        {
            return Error::CorruptedArchive;
        }
        
        val = std::stoull(text);
        return Error::NoError;
    }
    
    std::istream& in_;
};


#endif /* serializer_h */
