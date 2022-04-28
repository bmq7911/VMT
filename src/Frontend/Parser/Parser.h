#pragma once 

#include "Frontend/Lexer/Token.h"
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/AST/AST.h"
#include "SymbolTable/Env.h"
#include "Frontend/Parser/TokenReader.h"

//#include "Frontend/Symbols/Array.h"

/// <summary>
///  �����ݴ������Ҫ
/// </summary>


/// ����ӿڶ��������
/// ����
class Parser {
public:
    virtual std::shared_ptr<TokenReader> getTokenReader() = 0;
    virtual std::shared_ptr<ENV::Env>    getEnv() = 0;
    virtual std::shared_ptr<ENV::Env>    setEnv(std::shared_ptr<ENV::Env> env) = 0;
};
