/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include <iostream>
#include "Statement.h"
#include "Basic.h"

using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

void LetStatement::execute() {
    Basic::getInstance()->getSymbolTable()->set(var_, exp_);
}

void InputStatement::execute() {
    std::cout << "Enter value for " << var_ << " ? ";
    std::string line;
    std::getline(std::cin, line);
    TokenStream ts(line);
    auto exp = Expression::parse(ts);
    Basic::getInstance()->getSymbolTable()->set(var_, exp);
}

void PrintStatement::execute() {
    std::cout << exp_->toString() << std::endl;
}

void EndStatement::execute() {
    Basic::getInstance()->getProgram()->stop();
}


void GotoStatement::execute() {
    Basic::getInstance()->getProgram()->jumpTo(lineno_);
}

void IfStatement::execute() {
    int value1 = exp1_->eval();
        value2 = exp2_->eval(),
        diff = value1 - value2;
    if( (cmp_ == '<' && diff < 0) ||
        (cmp_ == '=' && diff == 0) ||
        (cmp_ == '>' && diff > 0)) {
        Basic::getInstance()->getProgram()->jumpTo(lineno_);
    }
}
