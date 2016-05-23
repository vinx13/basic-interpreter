#include <exception>
#include <string>

struct BasicException : public std::exception {
};

struct DivideByZeroException : public BasicException {
    virtual const char *what() const {
        return "DIVIDE BY ZERO";
    }
};

struct InvalidNumberException : public BasicException {
    virtual const char *what() const {
        return "INVALID NUMBER";
    }
};

struct VariableNotDefinedException : public BasicException {
    virtual const char *what() const {
        return "VARIABLE NOT DEFINED";
    }
};

struct LineNumberErrorException : public BasicException {
    virtual const char *what() const {
        return "LINE NUMBER ERROR";
    }
};

struct SyntaxErrorException : public BasicException {
    virtual const char *what() const {
        return "SYNTAX ERROR";
    }
};

