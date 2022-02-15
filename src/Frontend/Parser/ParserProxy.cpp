#include <assert.h>
#include <iostream>
#include "Frontend/Parser/ParserProxy.h"
#include "SymbolTable/TopEnv.h"

std::shared_ptr<ENV::Env>    ParserProxy::m_env= nullptr;

ParserProxy::ParserProxy(std::shared_ptr<TokenReader> parser) {
    m_reader = parser;
    _InitEnv();
}
std::shared_ptr<TokenReader> ParserProxy::getTokenReader() {
    return m_reader;
}
std::shared_ptr<ENV::Env> ParserProxy::getEnv()  {
    return m_env;
}
std::shared_ptr<ENV::Env> ParserProxy::setEnv(std::shared_ptr<ENV::Env>env)  {
    return m_env = env;
}
void                      ParserProxy::error(uint32_t line, uint32_t col, Tag expect, Tag but) {
    std::cout<<"in ["<< line<<","<<col<<"] expect "<< toString(expect)<<",but give "<< toString(but)  <<std::endl;
    abort();
}

void                      ParserProxy::error(const char *msg) {
    std::cout << std::string(msg)<< std::endl;
    abort();
}

bool                      ParserProxy::match(Token const& tok, Tag tag) {
    if (tok.match(tag)) {
        return true;
    }
    error(tok.m_location.row(), tok.m_location.col(), tag, tok.m_tag);
    return false;
}
Token ParserProxy::readToken() {
    return m_reader->readToken();
}

Token ParserProxy::fallbackToken() {
    return m_reader->fallbackToken();
}

Token ParserProxy::getToken() const {
    return m_reader->getToken();
}
std::shared_ptr<TokenReader> ParserProxy::get() {
    return m_reader;
}
void ParserProxy::_InitEnv() {
    static bool bInit = false;
    if (false == bInit) {
        m_env = ENV::getTopEnv();
        bInit = true;
    }
}

