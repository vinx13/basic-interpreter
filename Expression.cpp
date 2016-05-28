#include <string>
#include "Expression.h"
#include "Basic.h"
#include "Exception.h"


ExpressionPtr Expressions::parse(TokenStream &ts) {
    auto lhs = parsePrimary(ts);
    return parseBinary(ts, lhs, 0);
}

ExpressionPtr Expressions::parseBinary(TokenStream &ts, ExpressionPtr lhs, int precedence) {
    while (true) {
        auto token = ts.peek();
        if (!token || token->type != kTokenType::Operator) {
            return lhs; // no more tokens
        }
        ts.read(); // token is an operator, so it should be retrieved from TokenStream

        int token_prec = getPrecedence(token), next_prec;
        if (token_prec < precedence) {
            return lhs;
        }
        auto rhs = parsePrimary(ts);
        auto next = ts.peek();
        if (next && next->type == kTokenType::Operator &&
            (next_prec = getPrecedence(next)) > token_prec) {
            //next token is an operator with higher precedence
            rhs = parseBinary(ts, rhs, token_prec);
        }
        lhs = std::make_shared<CompoundExp>(token->value, lhs, rhs);
    }
}


ExpressionPtr Expressions::parsePrimary(TokenStream &ts) {
    auto token = ts.read();
    if (!token) {
        return std::shared_ptr<Expression>();
    }
    if (token->type == kTokenType::Number) {
        return std::make_shared<ConstantExp>(std::stoi(token->value));
    }
    if (token->type == kTokenType::Symbol) {
        return std::make_shared<IdentifierExp>(token->value);
    }
    if (token->type == kTokenType::Bracket && token->value == "(") {
        auto exp = parse(ts);
        token = ts.read(kTokenType::Bracket);
        if (token->value != ")") {
            throw SyntaxErrorException(); // empty expression in brackets or brackets do not match
        }
        return exp;
    }
    throw SyntaxErrorException();
}

int Expressions::getPrecedence(const std::shared_ptr<Token> token) {
    if (token->type != kTokenType::Operator) return 0;
    if (token->value == "+" || token->value == "-") return 1;
    if (token->value == "*" || token->value == "/") return 2;
    return 0;
}


/*
 * Implementation notes: the ConstantExp subclass
 * ----------------------------------------------
 * The ConstantExp subclass declares a single instance variable that
 * stores the value of the constant.  The eval method doesn't use the
 * value of state but needs it to match the general prototype for eval.
 */

ConstantExp::ConstantExp(int value) {
    this->value = value;
}

int ConstantExp::eval() const {
    return value;
}


kExpressionType ConstantExp::getType() const {
    return kExpressionType::Constant;
}


/*
 * Implementation notes: the IdentifierExp subclass
 * ------------------------------------------------
 * The IdentifierExp subclass declares a single instance variable that
 * stores the name of the variable.  The implementation of eval must
 * look this variable up in the evaluation state.
 */

IdentifierExp::IdentifierExp(const std::string &name) : name(name) {
}

int IdentifierExp::eval() const {
    auto st = Basic::getInstance()->getSymbolTable();
    return st->get(name);
}

kExpressionType IdentifierExp::getType() const {
    return kExpressionType::Identifier;
}


/*
 * Implementation notes: the CompoundExp subclass
 * ----------------------------------------------
 * The CompoundExp subclass declares instance variables for the operator
 * and the left and right subexpressions.  The implementation of eval 
 * evaluates the subexpressions recursively and then applies the operator.
 */

CompoundExp::CompoundExp(const std::string &op,
                         const std::shared_ptr<Expression> lhs,
                         const std::shared_ptr<Expression> rhs) :
        op(op), lhs(lhs), rhs(rhs) {
}


int CompoundExp::eval() const {
    int left = lhs->eval();
    int right = rhs->eval();
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") {
        if( !right) {
            throw DivideByZeroException();
        }
        return left / right;
    }
    throw SyntaxErrorException();
    return 0;
}

kExpressionType CompoundExp::getType() const {
    return kExpressionType::Compound;
}
