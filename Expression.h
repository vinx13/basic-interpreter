/*
 * This interface defines a class hierarchy for expressions,
 * which allows the client to represent and manipulate simple
 * binary expression trees.
 */

#ifndef _BASIC_EXPRESSION
#define _BASIC_EXPRESSION


#include <string>
#include <memory>
#include "TokenStream.h"

/*
 * Type: kExpressionType
 * --------------------
 * This enumerated type is used to differentiate the three different
 * expression types: Constant, Identifier, and Compound.
 */

enum class kExpressionType {
    Constant, Identifier, Compound
};

class Expression;

using ExpressionPtr = std::shared_ptr<Expression>;

/*
 * Class: Expression
 * -----------------
 * This class is used to represent a node in an expression tree.
 * Expression is an example of an abstract class, which defines
 * the structure and behavior of a set of classes but has no
 * objects of its own.  Any object must be one of the three
 * concrete subclasses of Expression:
 *
 *  1. ConstantExp   -- an integer constant
 *  2. IdentifierExp -- a string representing an identifier
 *  3. CompoundExp   -- two expressions combined by an operator
 *
 * The Expression class defines the interface common to all
 * Expression objects; each subclass provides its own specific
 * implementation of the common interface.
 */


class Expressions {
public:

    // Parse an expression from given TokenStream
    static ExpressionPtr parse(TokenStream &ts);

    // Parse a primary expression
    // number | symbol | '(' expression ')'
    static ExpressionPtr parsePrimary(TokenStream &ts);

    // Parse a compound expression with given lhs
    // (binary_operator expression) *
    static ExpressionPtr parseBinary(TokenStream &ts, ExpressionPtr lhs, int precedence);

    // Get precedence of given operator, return 0 if the given token is not an operator
    static int getPrecedence(const std::shared_ptr<Token> token);
};


class Expression {

public:

    virtual ~Expression() { }

    // Evaluates this expression and returns its value
    virtual int eval() const = 0;

    // Returns the type of the expression
    virtual kExpressionType getType() const = 0;

};

/*
 * Class: ConstantExp
 * ------------------
 * This subclass represents a constant integer expression.
 */

class ConstantExp : public Expression {

public:

/*
 * Constructor: ConstantExp
 * Usage: Expression *exp = new ConstantExp(value);
 * ------------------------------------------------
 * The constructor initializes a new integer constant expression
 * to the given value.
 */

    ConstantExp(int value);

    virtual int eval() const;

    virtual kExpressionType getType() const;

private:

    int value;

};

/*
 * Class: IdentifierExp
 * --------------------
 * This subclass represents an expression corresponding to a variable.
 */

class IdentifierExp : public Expression {

public:

/*
 * Constructor: IdentifierExp
 * Usage: Expression *exp = new IdentifierExp(name);
 * -------------------------------------------------
 * The constructor initializes a new identifier expression
 * for the variable named by name.
 */

    IdentifierExp(const std::string &name);

    virtual int eval() const;

    virtual kExpressionType getType() const;

private:

    std::string name;

    std::string getName() const;
};

/*
 * Class: CompoundExp
 * ------------------
 * This subclass represents a compound expression consisting of
 * two subexpressions joined by an operator.
 */

class CompoundExp : public Expression {

public:

/*
 * Constructor: CompoundExp
 * -------------------------------------------------------
 * The constructor initializes a new compound expression
 * which is composed of the operator (op) and the left and
 * right subexpression (lhs and rhs).
 */

    CompoundExp(const std::string &op, const ExpressionPtr lhs, const ExpressionPtr rhs);

    virtual int eval() const;

    virtual kExpressionType getType() const;

private:

    std::string op;
    std::shared_ptr<Expression> lhs, rhs;

};


#endif
