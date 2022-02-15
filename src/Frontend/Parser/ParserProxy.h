#pragma once
#include <memory>
#include "Frontend/Parser/Parser.h"
#include "Frontend/Parser/TokenReader.h"


class ParserProxy : public Parser {
public:
    ParserProxy( std::shared_ptr<TokenReader> );
    std::shared_ptr<TokenReader> getTokenReader() override final;
    std::shared_ptr<ENV::Env> getEnv() override final;
    std::shared_ptr<ENV::Env> setEnv(std::shared_ptr<ENV::Env> env) override final;

    void                      error( uint32_t line, uint32_t col, Tag expect, Tag but) override final;
    void                      error(const char *msg) override final;
    bool                      match( Token const& tok, Tag tag) override;
    Token readToken();
    Token fallbackToken();
    Token getToken() const;
    std::shared_ptr<TokenReader> get();
private:
    static void _InitEnv();
    std::shared_ptr<TokenReader> m_reader;
    static std::shared_ptr<ENV::Env>    m_env;
};