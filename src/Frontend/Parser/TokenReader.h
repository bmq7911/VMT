
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
    uint32_t getLineNum() const {
        return m_stream.getLineNum();
    }
    uint32_t getLineCol() const {
        return m_stream.getColNum();
    }
    std::string getLine() const {
        return m_stream.getLine();
    }

private:
    TokenStream            m_stream;
};

static inline TokenReader& operator>>(TokenReader& reader, Token& tok) {
    tok = reader.readToken();
    return reader;
}