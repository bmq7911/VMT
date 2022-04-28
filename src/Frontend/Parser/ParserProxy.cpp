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
Token ParserProxy::readToken() {
    return m_reader->readToken();
}

Token ParserProxy::advanceToken() {
    return m_reader->advanceToken();
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

