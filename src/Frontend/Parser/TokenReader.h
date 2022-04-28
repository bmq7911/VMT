
#pragma once
#include "Frontend/Lexer/Lexer.h"

class TokenReader {
public:
    TokenReader(std::shared_ptr<Lexer> lex) 
        :  m_lexer(lex)
    {
        m_advanceToken = m_lexer->scan();
    }
    Token advanceToken() {
        return m_advanceToken;
    }
    Token readToken() {
        m_currentToken = m_advanceToken;
        m_advanceToken = m_lexer->scan();
        return m_currentToken;
    }
    Token getToken() const {
        return m_currentToken;
    }
private:
    std::shared_ptr<Lexer> m_lexer;
    Token                  m_advanceToken;
    Token                  m_currentToken;
};
