#include <cctype>
#include <iostream>
#include <string>
#include "Basic.h"
#include "Exception.h"
#include "TokenStream.h"

std::shared_ptr<Basic> Basic::instance__ = std::shared_ptr<Basic>(new Basic());

void Basic::run() {
    std::string line;
    while (true) {
        try {
            std::getline(std::cin, line);
           processLine(line);
        } catch (BasicException & e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}


void Basic::processLine(const std::string &line) {
    TokenStream ts(line);

    auto token = ts.peek();
    
    if(token->type == kTokenType::Number) {
   
    } else if(token->type == kTokenType::Command) {
        handleCommand(token->value);
        ts.read();
    } else if(token->type == kTokenType::Keyword) {
        auto stmt = Statement::parse(ts);
        if(stmt->isImmediate() == false){
            throw SyntaxErrorException();
        } else {
            stmt->execute();
        }
    } else {
        throw SyntaxErrorException();
    }

}


int main() {
    Basic::getInstance()->run();

    return 0;
}

