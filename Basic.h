#ifndef _BASIC_BASIC
#define _BASIC_BASIC


#include <map>
#include <functional>
#include "SymbolTable.h"
#include "TokenStream.h"
#include "Program.h"

class Basic {
public:
    static std::shared_ptr<Basic> getInstance() { return instance__; }

    void run();
    
    std::shared_ptr<SymbolTable> getSymbolTable() { return symbols_; }
    
    std::shared_ptr<Program> getProgram() { return program_; }

private:
    Basic() { }
    void processLine(const std::string &line);
    
    void handleCommand(const std::string &command);

    std::shared_ptr<Basic> instance__;

    std::shared_ptr<Program> program_;
    std::shared_ptr<SymbolTable> symbols_;
    
    std::map<std::string, std::function<void()> > command_handlers_;
};
       
#endif
