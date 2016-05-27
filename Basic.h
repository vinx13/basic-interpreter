#ifndef _BASIC_BASIC
#define _BASIC_BASIC


#include <map>
#include <functional>
#include "SymbolTable.h"
#include "TokenStream.h"
#include "Program.h"

using CmdHandler = std::function<void()>;

class Basic {
public:
    
    static std::shared_ptr<Basic> getInstance() { return instance__; }

    void run();
    
    std::shared_ptr<SymbolTable> getSymbolTable() { return symbols_; }
    
    std::shared_ptr<Program> getProgram() { return program_; }

private:
    static std::shared_ptr<Basic> instance__;
    
    Basic();

    void processLine(const std::string &line);
    
    void handleCommand(const std::string &command);

    void printHelp() const;

    std::shared_ptr<Program> program_;
    std::shared_ptr<SymbolTable> symbols_;
    
    std::map<std::string, CmdHandler > command_handlers_;
};
       

#endif
