cmake_minimum_required(VERSION 3.4)
project(Basic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES
    Basic.cpp
    Basic.h
    Exception.h
    Expression.cpp
    Expression.h
    Program.cpp
    Program.h
    Statement.cpp
    Statement.h
    SymbolTable.cpp
    SymbolTable.h
    Token.h
    TokenStream.cpp
    main.cpp
)

add_executable(Basic ${SOURCE_FILES})
