#ifndef _BASIC_EXCEPTION
#define _BASIC_EXCEPTION


#include <exception>
#include <string>

struct BasicException : public std::exception {
};

struct DivideByZeroException : public BasicException {
    virtual const char *what() const noexcept {
        return "DIVIDE BY ZERO";
    }
};

struct InvalidNumberException : public BasicException {
    virtual const char *what() const noexcept {
        return "INVALID NUMBER";
    }
};

struct VariableNotDefinedException : public BasicException {
    virtual const char *what() const noexcept {
        return "VARIABLE NOT DEFINED";
    }
};

struct LineNumberErrorException : public BasicException {
    virtual const char *what() const noexcept {
        return "LINE NUMBER ERROR";
    }
};

struct SyntaxErrorException : public BasicException {
    virtual const char *what() const noexcept {
        return "SYNTAX ERROR";
    }
};


#endif

