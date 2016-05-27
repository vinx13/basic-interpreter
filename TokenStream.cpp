#include <cctype>
#include <algorithm>
#include "Exception.h"
#include "TokenStream.h"

TokenStream::TokenStream(const std::string &line) {
    setInput(line);
}

void TokenStream::setInput(const std::string &line){
    src_ = line;
    cur_ = src_.begin();
    end_ = src_.end();
    
    scanNext();
}

std::shared_ptr<Token> TokenStream::read() {
    auto token = token_;
    scanNext();
    return token;
}

std::string TokenStream::getString() const {
    return src_;
}

std::shared_ptr<Token> TokenStream::read(kTokenType expect) {
    auto token = token_;
    scanNext();
    if(!token || expect != token->type) {
        throw SyntaxErrorException();
    }
    return token;
}

std::shared_ptr<Token> TokenStream::peek() const {
    return token_;
}


void TokenStream::scanNext() {
    while(cur_ != end_ && *cur_ == ' ')
        ++cur_;

    if(isdigit(*cur_)) {
        auto start = cur_;
        while(++cur_ != end_ && std::isdigit(*cur_))
            ;
        token_ = std::make_shared<Token>(kTokenType::Number, std::string(start, cur_));
        return;
    }
    if(std::isalpha(*cur_)){
        auto start = cur_;
        while(++cur_ != end_ && std::isalpha(*cur_))
            ;
        std::string word(start, cur_);

        //check if the word is keyword or command
        if(isKeyword(word)) {
            token_ = std::make_shared<Token>(kTokenType::Keyword, word);
            return;
        }
        if(isCommand(word)) {
            token_ = std::make_shared<Token>(kTokenType::Command, word);
            return;
        }
        token_ = std::make_shared<Token>(kTokenType::Symbol, word);
        return;
    }
    switch(*cur_){
        case '+': case '-': case '*': case '/': 
            token_ = std::make_shared<Token>(kTokenType::Operator, std::string(cur_, cur_ + 1));
            ++cur_;
            return;
        case '(': case ')':
            token_ = std::make_shared<Token>(kTokenType::Bracket, std::string(cur_, cur_ + 1));
            ++cur_;
            return;
        case '<': case '>': case '=':
            token_ = std::make_shared<Token>(kTokenType::Compare, std::string(cur_, cur_ + 1));
            ++cur_;
            return;
    }

    throw SyntaxErrorException();
}

bool TokenStream::isCommand(const std::string &word) const {
    static const std::string commands[] = {
        "RUN", "LIST", "CLEAR", "QUIT", "HELP"
    };
    return std::find(std::begin(commands), std::end(commands), word) != std::end(commands);
}

bool TokenStream::isKeyword(const std::string &word) const {
    static const std::string keywords[] = {
        "REM", "LET", "PRINT", "INPUT", "END", "GOTO", "IF", "THEN"
    };
    return std::find(std::begin(keywords), std::end(keywords), word) != std::end(keywords);
}
