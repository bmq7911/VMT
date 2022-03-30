#pragma once
#include <list>
#include "Frontend/Lexer/Lexer.h"

class TokenStream {
public:
    TokenStream( std::shared_ptr<Lexer> lexer)
        : m_lex(lexer)
        , m_bFallback(false)
    {
    }
    Token readToken() {
        if (false == m_bFallback) {
            m_forward = m_current;
            m_current = m_lex->scan();
            return m_current;
        }
        else  {
            m_bFallback = false;
            return m_current;
        }

    }
    Token fallbackToken( ) {
        /// 1.现在处理未回退状态
        m_bFallback = true;
        return m_current;
    }
    Token getToken() const {
        return m_current;
    }
private:
    std::shared_ptr<Lexer> m_lex;
    Token m_forward;
    Token m_current;
    bool  m_bFallback;
};