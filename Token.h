#include <string>

enum class kTokenType {
    Number, Symbol, Keyword, Command, 
    Operator, Compare, Bracket
};

struct Token {
    kTokenType type;
    std::string value;
};
