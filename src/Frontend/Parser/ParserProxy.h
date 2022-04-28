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

    Token readToken();
    Token advanceToken();
    Token getToken() const;
    std::shared_ptr<TokenReader> get();
private:
    static void _InitEnv();
    std::shared_ptr<TokenReader> m_reader;
    static std::shared_ptr<ENV::Env>    m_env;
};