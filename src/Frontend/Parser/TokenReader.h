
#pragma once
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/Lexer/TokenStream.h"

class TokenReader {
public:
    TokenReader(std::shared_ptr<Lexer> lex) 
        : m_stream(lex)
    {}
    Token readToken() {
        return m_stream.readToken();
    }
    Token fallbackToken() {
        return m_stream.fallbackToken();
    }
    Token getToken() const {
        return m_stream.getToken();
    }
    friend TokenReader& operator>>(TokenReader& reader, Token& tok);


private:
    TokenStream            m_stream;
};

static inline TokenReader& operator>>(TokenReader& reader, Token& tok) {
    tok = reader.readToken();
    return reader;
}