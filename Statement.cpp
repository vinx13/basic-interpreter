#include <string>
#include <iostream>
#include <utility>
#include "Statement.h"
#include "Basic.h"
#include "Expression.h"
#include "Exception.h"
#include "TokenStream.h"

std::map<std::string, ParserFunc> Statement::parsers__ {
    { 
        "REM", 
        [](TokenStream &ts) { 
            return std::make_shared<RemStatement>();
        }
    },
    {
        "LET",
        [](TokenStream &ts) {
            auto var = ts.read(kTokenType::Symbol);
            auto exp = Expression::parse(ts);
            return  std::make_shared<LetStatement>(var->value, exp);
        }
    },
    {
        "PRINT",
        [](TokenStream &ts) {
            auto exp = Expression::parse(ts);
            return std::make_shared<PrintStatement>(exp);
        }
    },
    {
        "INPUT",
        [](TokenStream &ts) {
            auto var = ts.read(kTokenType::Symbol);
            return std::make_shared<InputStatement>(var);
        }
    },
    {
        "END",
        [](TokenStream &ts) {
            return std::make_shared<EndStatement>();
        }
    },
    {
        "GOTO",
        [](TokenStream &ts) {
            auto lineno = ts.read(kTokenType::Number);
            return std::make_shared<GotoStatement>(lineno->value);
        } 
    },
    {
        "IF",
        [](TokenStream &ts) {
            auto exp1 = Expression::parse(ts);
            auto cmp = ts.read(kTokenType::Compare);
            auto exp2 = Expression::parse(ts);
            auto then = ts.read(kTokenType::Command);
            if(then->value != "THEN") {
                throw SyntaxErrorException();
            }
            auto lineno = ts.read(kTokenType::Number);
            return std::make_shared<IfStatement>(exp1, cmp->value, exp2, lineno->value);
        }
    }
};
        

StatementPtr Statement::parse(TokenStream &ts) {
    auto keyword = ts.read(kTokenType::Command)->value;
    return parsers__.at(keyword)(ts);
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
    int value1 = exp1_->eval(),
        value2 = exp2_->eval(),
        diff = value1 - value2;
    if( (cmp_ == "<" && diff < 0) ||
        (cmp_ == "=" && diff == 0) ||
        (cmp_ == ">" && diff > 0)) {
        Basic::getInstance()->getProgram()->jumpTo(lineno_);
    }
}
