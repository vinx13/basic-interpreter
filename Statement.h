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
#include "Expression.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute() = 0;

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
    std::shared_ptr<Expression> exp_;
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

    PrintStatement(std::shared_ptr<Expression> exp): exp_(exp) {  }

    virtual void execute();

private:
    std::shared_ptr<Expression> exp_;
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

    IfStatement(const std::shared_ptr<Expression> exp1, const std::shared_ptr<Expression> exp2, char cmp, int lineno):
        exp1_(exp1), exp2_(exp2), cmp_(cmp), lineno_(lineno) {  }

    virtual void execute();

private:
    const std::shared_ptr<Expression> exp1_, exp2_;
    const char cmp_;
    const int lineno_;
};

#endif
