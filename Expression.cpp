#include <string>
#include "Expression.h"
#include "Basic.h"
#include "Exception.h"
/*
 * Implementation notes: the Expression class
 * ------------------------------------------
 * The Expression class declares no instance variables and needs no code.
 */

Expression::Expression() {
   /* Empty */
}

Expression::~Expression() {
   /* Empty */
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

int ConstantExp::eval() {
   return value;
}

std::string ConstantExp::toString() {
    return std::to_string(value);
}

kExpressionType ConstantExp::getType() {
   return kExpressionType::Constant;
}

int ConstantExp::getValue() {
   return value;
}

/*
 * Implementation notes: the IdentifierExp subclass
 * ------------------------------------------------
 * The IdentifierExp subclass declares a single instance variable that
 * stores the name of the variable.  The implementation of eval must
 * look this variable up in the evaluation state.
 */

IdentifierExp::IdentifierExp(std::string name):name(name) {
}

int IdentifierExp::eval() {
    auto st = Basic::getInstance()->getSymbolTable();
    auto exp = st->get(name);
    if(!exp) {
        //TODO
    }
    return exp->eval();
}

std::string IdentifierExp::toString() {
   return name;
}

kExpressionType IdentifierExp::getType() {
   return kExpressionType::Identifier;
}

std::string IdentifierExp::getName() {
   return name;
}

/*
 * Implementation notes: the CompoundExp subclass
 * ----------------------------------------------
 * The CompoundExp subclass declares instance variables for the operator
 * and the left and right subexpressions.  The implementation of eval 
 * evaluates the subexpressions recursively and then applies the operator.
 */

CompoundExp::CompoundExp(std::string op, std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs) :
    op(op), lhs(lhs), rhs(rhs) {
}


int CompoundExp::eval() {
/*   if (op == "=") {
      if (lhs->getType() != kExpressionType::Identifier) {
        //TODO
      }
      int val = rhs->eval(state);
      state.setValue(((IdentifierExp *) lhs)->getName(), val);
      return val;
   }*/
   int left = lhs->eval();
   int right = rhs->eval();
   if (op == "+") return left + right;
   if (op == "-") return left - right;
   if (op == "*") return left * right;
   if (op == "/") return left / right;
   throw SyntaxErrorException();
   return 0;
}

std::string CompoundExp::toString() {
   return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
}

kExpressionType CompoundExp::getType() {
   return kExpressionType::Compound;
}

std::string CompoundExp::getOp() {
   return op;
}

ExpressionPtr CompoundExp::getLHS() {
   return lhs;
}

ExpressionPtr CompoundExp::getRHS() {
   return rhs;
}
