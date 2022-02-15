#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>
#include <fstream>

#include "Frontend/Lexer/Tag.h"
#include "Frontend/Lexer/Token.h"
#include "Frontend/Lexer/Identifier.h"
#include "Frontend/Lexer/KeyWord.h"

/// 整个前端过程还是复杂的,整个编译器的设计是三段式的,但是还是太复杂了,还是有太多的东西需要考虑
/// 最基本的就是如何做到,
class Lexer {
public: 
public:
    Lexer();
    Lexer(const char * filePath);
public:
    Token scan();
    uint32_t getLineNum() const;
    uint32_t getColNum() const;
    std::string getLine() const;
private:
    void _Readch();
    bool _Readch(char c);
    void _ForwardSearch();
    char _OffsetRead(int32_t offet);
    Token _GenToken(Tag tag) const;
    FileLocation _GenFileLocation() const;
    void  _ResumeReadPtr();
    void _Reserve(Identifier  * w);


private:
    Token _ScanConstant();
    Token _ScanIdentifier();
    Token _ScanPunctuation();
private:
    char m_peek{ ' ' };
    int m_line{1};
    int m_col{1};

    std::shared_ptr<KeyWord>              m_keyWord;
    std::map<std::string, Identifier*>    m_Identifier;
    std::string m_strSrc;

    uint32_t m_lineStart{ 0 };
    uint32_t m_index{ 0 };
    uint32_t m_readPtr{0xFFFFFFFF};
    uint32_t m_forwardPtr{0xFFFFFFFF };
};
