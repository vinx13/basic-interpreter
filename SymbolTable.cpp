#include "SymbolTable.h"
#include "Exception.h"

int SymbolTable::get(const std::string &identifier) {
    auto iter = symbols_.find(identifier);
    if (iter == symbols_.end()) {
        throw VariableNotDefinedException();
    }
    return iter->second;
}

void SymbolTable::set(const std::string &identifier, int value) {
    symbols_[identifier] = value;
}

bool SymbolTable::remove(const std::string &identifier) {
    auto iter = symbols_.find(identifier);
    if (iter == symbols_.end()) {
        return false;
    }
    symbols_.erase(iter);
    return true;
}

void SymbolTable::clear() {
    symbols_.clear();
}
