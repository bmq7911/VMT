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
    Lexer(const char * filePath);
public:
    virtual Token scan();
    virtual void  startToken();
    uint32_t getLineNum() const;
    uint32_t getColNum() const;
    std::string getLine() const;
private:
    void _Readch();
    bool _Readch(char c);
    void _ForwardSearch();
    char _OffsetRead(int32_t offet);
    Token _GenToken(TokenId tag) const;
    FileLocation _GenFileLocation() const;
    void  _ResumeReadPtr();


private:
    Token _ScanConstant();
    Token _ScanIdentifier();
    Token _ScanPunctuation();
private:
    uint32_t m_peek{ ' ' };
    int m_line{1};
    int m_col{1};

    std::string m_strSrc;

    uint32_t m_lineStart{ 0 };
    uint32_t m_index{ 0 };
    uint32_t m_readPtr{0xFFFFFFFF};
    uint32_t m_forwardPtr{0xFFFFFFFF };
};

