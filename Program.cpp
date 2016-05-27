#include <string>
#include <utility>
#include <iostream>
#include "Program.h"
#include "TokenStream.h"
#include "Statement.h"

void Program::addStatement(const std::string &source) {
    TokenStream ts(source);
    auto lineno = ts.read(kTokenType::Number);
    statements_[std::stoi(lineno->value)] = std::make_pair(
        source,
        Statement::parse(ts)
    ); 

}

void Program::removeStatement(int line) {
    auto iter = statements_.find(line);
    if(iter != statements_.end()) {
        statements_.erase(iter);
    }
}

void Program::jumpTo(int lineno) {
    cur_line_ = lineno;
}

void Program::clear() {
    statements_.clear();
}

void Program::stop() {
    stopped_ = true;
}

void Program::run() {
    auto iter = statements_.begin();
    stopped_ = false;
    
    while(!stopped_ && iter != statements_.end()) {
        cur_line_ = iter->first;
        iter->second.second->execute();
        
        if(cur_line_ != iter->first) { //jumpTo is called
            iter = statements_.find(cur_line_);
        } else {
            ++iter;
        }
    }
}

void Program::printStatements() const {
    for(auto iter = statements_.begin(); iter != statements_.end(); ++iter) {
        std::cout << iter->second.first << std::endl;
    }
    std::cout << std::endl;
}

