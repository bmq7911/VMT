#include <assert.h>
#include <iostream>
#include "Frontend/Parser/ParserProxy.h"


ParserProxy::ParserProxy(std::shared_ptr<TokenReader> parser) {
    m_reader = parser;
}
std::shared_ptr<TokenReader> ParserProxy::getTokenReader() {
    return m_reader;
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

