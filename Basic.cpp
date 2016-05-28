#include <cctype>
#include <iostream>
#include <string>
#include "Basic.h"
#include "Exception.h"
#include "TokenStream.h"

std::shared_ptr<Basic> Basic::instance__ = std::shared_ptr<Basic>(new Basic());

Basic::Basic() : command_handlers_  {
        {
            "RUN",
            [this]() {
                this->program_->run();
            }
        },
        {
            "LIST",
            [this]() {
                this->program_->printStatements();
            }
        },
        {
            "CLEAR",
            [this]() {
                this->program_->clear();
                this->symbols_->clear();
            }
        },
        {
            "QUIT",
            [this]() {
                std::exit(EXIT_SUCCESS);
            }
        },
        {
            "HELP",
            [this]() {
                this->printHelp();
            }
        }
    }
{
    program_ = std::make_shared<Program>();
    symbols_ = std::make_shared<SymbolTable>();
}

void Basic::handleCommand(const std::string &command) {
    auto &func = command_handlers_.at(command);
    func();
}

void Basic::run() {
    std::string line;
    while (true) {
        try {
            std::getline(std::cin, line);
            processLine(line);
        } catch (BasicException & e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void Basic::processLine(const std::string &line) {
    TokenStream ts(line);

    auto token = ts.peek();

    if(!token) {
        return; //empty line
    }

    if(token->type == kTokenType::Number) {
        // add or remove a statement
        ts.read(); // eat line number
        if(!ts.peek()) {
            // no input after line number
            program_->removeStatement(std::stoi(token->value));
        } else {
            program_->addStatement(ts.getString());
        }
    } else if(token->type == kTokenType::Command) {
    
        handleCommand(token->value);
        ts.read();
    
    } else if(token->type == kTokenType::Keyword) {
    
        const std::string immediate_stmts[] = { "LET", "INPUT", "PRINT" }; // statements that can be executed directly without given a line number
        if(std::find(std::begin(immediate_stmts), std::end(immediate_stmts), token->value) == std::end(immediate_stmts)){
            throw SyntaxErrorException();
        }
        auto stmt = Statements::parse(ts);
        stmt->execute();
    
    } else {
        throw SyntaxErrorException();
    }

}

void Basic::printHelp() const {
    const std::string help = 
        "RUN -- This command starts program execution beginning at the lowest-numbered line\n"\
        "LIST -- This command lists the steps in the program in numerical sequence\n"\
        "CLEAR -- This command deletes all program and variables\n"\
        "QUIT -- This command exits from the BASIC interpreter by calling exit(0)\n"\
        "HELP -- This command provides a simple help message describing your interpreter\n";
    std::cout << help << std::endl;
}

