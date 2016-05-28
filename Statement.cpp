#include <string>
#include <iostream>
#include "Statement.h"
#include "Basic.h"
#include "Exception.h"

std::map<std::string, ParserFunc> Statements::parsers__{
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
            auto token = ts.read(kTokenType::Compare);
            if (token->value != "=") {
                throw SyntaxErrorException();
            }
            auto exp = Expressions::parse(ts);
            return std::make_shared<LetStatement>(var->value, exp);
        }
    },
    {
        "PRINT",
        [](TokenStream &ts) {
            auto exp = Expressions::parse(ts);
            return std::make_shared<PrintStatement>(exp);
        }
    },
    {
        "INPUT",
        [](TokenStream &ts) {
            auto var = ts.read(kTokenType::Symbol);
            return std::make_shared<InputStatement>(var->value);
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
            return std::make_shared<GotoStatement>(std::stoi(lineno->value));
        }
    },
    {
        "IF",
        [](TokenStream &ts) {
            auto exp1 = Expressions::parse(ts);
            auto cmp = ts.read(kTokenType::Compare);
            auto exp2 = Expressions::parse(ts);
            auto then = ts.read(kTokenType::Keyword);
            if (then->value != "THEN") {
                throw SyntaxErrorException();
            }
            auto lineno = ts.read(kTokenType::Number);
            return std::make_shared<IfStatement>(exp1, cmp->value, exp2, std::stoi(lineno->value));
        }
    }
};


StatementPtr Statements::parse(TokenStream &ts) {
    auto keyword = ts.read(kTokenType::Keyword)->value;
    return parsers__.at(keyword)(ts);
}

void LetStatement::execute() {
    Basic::getInstance()->getSymbolTable()->set(var_, exp_->eval());
}

void InputStatement::execute() {
    while (true) {
        std::cout << " ? ";
        std::string line;
        std::getline(std::cin, line);
        try {
            int value = parseNumber(line);
            Basic::getInstance()->getSymbolTable()->set(var_, value);
            return;
        } catch (InvalidNumberException &e) {
            std::cout << e.what() << std::endl;
        }
    }
    //TokenStream ts(line);
    //auto exp = Expressions::parse(ts);
    //Basic::getInstance()->getSymbolTable()->set(var_, exp);
}

int InputStatement::parseNumber(const std::string &line) const {
    try {
        size_t pos;
        int value = stoi(line, &pos);
        if (pos != line.size()) {
            throw InvalidNumberException(); // redundant tokens after the number
        }
        return value;
    } catch (std::invalid_argument &e) {
        throw InvalidNumberException();
    }
}

void PrintStatement::execute() {
    std::cout << std::to_string(exp_->eval()) << std::endl;
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
    if ((cmp_ == "<" && diff < 0) ||
        (cmp_ == "=" && diff == 0) ||
        (cmp_ == ">" && diff > 0)) {
        Basic::getInstance()->getProgram()->jumpTo(lineno_);
    }
}
