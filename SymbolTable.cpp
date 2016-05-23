#include "SymbolTable.h"

SymbolTable::ExpressionPtr SymbolTable::get(const std::string &identifier) {
    return symbols_[identifier];
}

void SymbolTable::set(const std::string &identifier, ExpressionPtr value) {
    symbols_[identifier] = value;
}

bool SymbolTable::remove(const std::string &identifier) {
    auto iter = symbols_.find(identifier);
    if(iter == symbols_.end()){
        return false;
    }
    symbols_.erase(iter);
    return true;
}
