#pragma once
#include <memory>
#include "Frontend/Parser/Parser.h"
#include "Frontend/Parser/TokenReader.h"


class ParserProxy : public Parser {
public:
    ParserProxy( std::shared_ptr<TokenReader> );
    std::shared_ptr<TokenReader> getTokenReader() override final;

    Token readToken();
    Token advanceToken();
    Token getToken() const;
    std::shared_ptr<TokenReader> get();
private:
    std::shared_ptr<TokenReader> m_reader;
};