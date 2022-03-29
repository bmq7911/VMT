#pragma once 

#include "Frontend/Lexer/Token.h"
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/AST/AST.h"
#include "SymbolTable/Env.h"
#include "Frontend/Parser/TokenReader.h"

//#include "Frontend/Symbols/Array.h"

/// <summary>
///  理解这份代码很重要
/// </summary>


/// 这个接口定义错误了
/// 按道
class Parser {
public:
    virtual std::shared_ptr<TokenReader> getTokenReader() = 0;
    virtual std::shared_ptr<ENV::Env>    getEnv() = 0;
    virtual std::shared_ptr<ENV::Env>    setEnv(std::shared_ptr<ENV::Env> env) = 0;
    virtual void                         error( uint32_t line, uint32_t col, TokenId expect, TokenId but) = 0;
    virtual void                         error(const char *msg) = 0;
    virtual bool                         match( Token const& tok, TokenId tag) = 0;
};
