#pragma once 
#include "Frontend/Parser/TokenReader.h"
#include "Frontend/AST/Ast.h"


class Parser {
public:
    virtual std::shared_ptr<TokenReader> getTokenReader() = 0;
};
