#include <string>
#include <map>
#include <memory>

class Expression;

class SymbolTable {
public:
    using ExpressionPtr = std::shared_ptr<Expression>;

    // Get the value of specified identifier, return null if the identifier do not exists
    ExpressionPtr get(const std::string &identifier);

    // Set the value of specified identifier
    void set(const std::string &identifier, ExpressionPtr value);
    
    // Remove the value of specified identifier, return true if the identifier exists
    bool remove(const std::string &identifier);

private:
    std::map<std::string, ExpressionPtr> symbols_;
};
