#include <string>
#include <map>
#include <memory>
#include "Expression.h"

class SymbolTable {
public:
    using ExpressionPtr = std::shared_ptr<Expression>;

    ExpressionPtr get(const std::string &identifier);
    void set(const std::string &identifier, ExpressionPtr value);
    bool remove(const std::string &identifier);

private:
    std::map<std::string, ExpressionPtr> symbols_;
};
