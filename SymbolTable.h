#ifndef _BASIC_SYMBOLTABLE
#define _BASIC_SYMBOLTABLE


#include <string>
#include <map>
#include <memory>

class SymbolTable {
public:

    // Get the value of specified identifier, return null if the identifier do not exists
    int get(const std::string &identifier);

    // Set the value of specified identifier
    void set(const std::string &identifier, int value);
    
    // Remove the value of specified identifier, return true if the identifier exists
    bool remove(const std::string &identifier);

    // Clear all symbols
    void clear();

private:
    std::map<std::string, int> symbols_;
};


#endif

