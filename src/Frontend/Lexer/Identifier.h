#pragma once
#include "Frontend/Lexer/Token.h"

/// �������޷�����������,�����Ǵʷ�����,���û��Ҫ�������������Щ��Ϣ
class Identifier : public Token {
public:
    using super = Token;
    Identifier()
        :Token(Tag::unknown)
    {
    }
    Identifier(std::string const& s, Tag tag)
        : super(tag)
    {
        m_lexeme = s;
    }
    std::string toString() const {
        return m_lexeme;
    }
    bool operator==(Identifier const & word) const {
        return m_lexeme == word.m_lexeme;
    }
    operator bool() const {
        return super::operator bool();
    }
public:
    std::string m_lexeme;
};