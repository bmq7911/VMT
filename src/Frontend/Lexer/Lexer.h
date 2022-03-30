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

/// ����ǰ�˹��̻��Ǹ��ӵ�,���������������������ʽ��,���ǻ���̫������,������̫��Ķ�����Ҫ����
/// ������ľ����������,
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

