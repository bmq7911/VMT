#pragma once 

#include "Frontend/Lexer/Token.h"
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/AST/Ast.h"
#include "SymbolTable/Env.h"
#include "Frontend/Parser/TokenReader.h"


class Parser {
public:
    virtual std::shared_ptr<TokenReader> getTokenReader() = 0;
    virtual std::shared_ptr<ENV::Env>    getEnv() = 0;
    virtual std::shared_ptr<ENV::Env>    setEnv(std::shared_ptr<ENV::Env> env) = 0;
};
