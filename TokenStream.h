#ifndef _BASIC_TOKENSTREAM
#define _BASIC_TOKENSTREAM


#include <memory>
#include <string>
#include "Token.h"

class TokenStream {
public:
    
    // Create a lexer to analyze given line
    TokenStream(const std::string &line);

    // Get current token and move the cursor to next one 
    std::shared_ptr<Token> read();

    // Get current token and move the cursor to next one, 
    // if the type of current token does not match 'expect', 
    // SyntaxErrorException will be raised after updating the cursor
    std::shared_ptr<Token> read(kTokenType expect);
    
    // Get current token without updating the cursor
    std::shared_ptr<Token> peek() const;

    // Get the string being read from
    std::string getString() const;
private:

    void setInput(const std::string &line);
    
    void scanNext();

    void ltrim();

    bool isCommand(const std::string &word) const;
    
    bool isKeyword(const std::string &word) const;

    std::shared_ptr<Token> token_;
    std::string src_;
    std::string::iterator cur_, end_;



};


#endif

