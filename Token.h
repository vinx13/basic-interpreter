#ifndef _BASIC_TOKEN
#define _BASIC_TOKEN


#include <string>

enum class kTokenType {
    Number, Symbol, Keyword, Command, 
    Operator, Compare, Bracket
};

struct Token {
    kTokenType type;
    std::string value;
    
    Token(kTokenType type, const std::string &value): type(type), value(value) { }
};


#endif
