#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>
#include <fstream>

#include "Frontend/Lexer/TokenId.h"
#include "Frontend/Lexer/Token.h"
#include "Frontend/Lexer/File.h"

/// 整个前端过程还是复杂的,整个编译器的设计是三段式的,但是还是太复杂了,还是有太多的东西需要考虑
/// 最基本的就是如何做到,
/// 
class Lexer {
public: 
public:
    Lexer();
public:
    virtual Token scan();
    virtual void  startToken();
    virtual Token genToken( TokenId );
    virtual std::string_view genLexeme();
    virtual void nextLine();
private:
    virtual int32_t _Readch() = 0;
private:
    Token _ScanConstant();
    Token _ScanIdentifier();
    Token _ScanPunctuation();
private:
    uint32_t m_peek{ ' ' };
};

