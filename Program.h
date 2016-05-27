#ifndef _BASIC_PROGRAM
#define _BASIC_PROGRAM


#include <map>
#include <utility>
#include "Statement.h"

class Program {
public:
    // Add a statement to be executed, 
    // this statement is stored in a std::string, which should start with a line number
    void addStatement(const std::string &source);
    
    // Remove the statement with given line number
    void removeStatement(int lineno);

    // Remove all statements
    void clear();

    // Start executing stoted statements until stop is called or all statements are executed
    void run();

    // Stop execution
    void stop();

    // Jump to the statement with given line number
    void jumpTo(int lineno);

    // Print the original string of stored statements
    void printStatements() const;

private:

    std::map<int, std::pair<std::string, StatementPtr> > statements_;
    bool stopped_ = false;

    int cur_line_ = -1;
};


#endif

