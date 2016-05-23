#include "token.h"
#include <memory>
#include <string>

class TokenStream {
public:
    
    // Create a lexer to analyze given line
    TokenStream(const std::string &line);

    // Get current token and move the cursor to next one 
    std::shared_ptr<Token> read();

    // Get current token without updating the cursor
    std::shared_ptr<Token> peek() const;
    
private:

    void reset();

    void setInput(const std::string &line);
    
    void scanNext();
    
    bool isCommand(const std::string &word) const;
    
    bool isKeyword(const std::string &word) const;

    std::shared_ptr<Token> token_;
    std::string src_;
    std::string::iterator cur_, end_;
    
};
