/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _BASIC_STATEMENT
#define _BASIC_STATEMENT


#include <string>
#include <memory>
#include <map>
#include <functional>
#include "Expression.h"


class Statement;
using StatementPtr = std::shared_ptr<Statement>;
using ParserFunc = std::function<StatementPtr(TokenStream &)>;


/*
 * Base of classes representating control statement of sequencial statement in BASIC
 */
class Statement {

public:

    static StatementPtr parse(TokenStream &ts);

    virtual ~Statement() { }

    // Execute this statement
    virtual void execute() = 0;

private:
    static std::map<std::string, ParserFunc> parsers__;
};

class RemStatement: public Statement {
public:

    virtual void execute() { }
};

class LetStatement: public Statement {
public:

    LetStatement(const std::string &identifier, std::shared_ptr<Expression> exp) :var_(identifier), exp_(exp) {  }

    virtual void execute();

private:
    std::string var_;
    const ExpressionPtr exp_;
};

class InputStatement: public Statement {
public:

    InputStatement(const std::string &identifier): var_(identifier) {  }

    virtual void execute();

private:
    std::string var_;
};

class PrintStatement: public Statement {
public:

    PrintStatement(ExpressionPtr exp): exp_(exp) {  }

    virtual void execute();

private:
    const ExpressionPtr exp_;
};

class EndStatement: public Statement {
public:

    virtual void execute();
};

class GotoStatement: public Statement {
public:

    GotoStatement(int lineno): lineno_(lineno) {  }

    virtual void execute();

private:
    int lineno_;
};

class IfStatement: public Statement {
public:

    IfStatement(const ExpressionPtr exp1, const ExpressionPtr exp2, const std::string &cmp, int lineno):
        exp1_(exp1), exp2_(exp2), cmp_(cmp), lineno_(lineno) {  }

    virtual void execute();

private:
    const ExpressionPtr exp1_, exp2_;
    const std::string cmp_;
    const int lineno_;
};

#endif
