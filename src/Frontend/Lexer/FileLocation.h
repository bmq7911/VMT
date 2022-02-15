#pragma once
#include "ADT/StringRef.h"


class FileLocation {
    friend class Lexer;
public:
    FileLocation() 
        : m_row(0)
        , m_col(0)
        , m_lexeme()
    {
    }
    FileLocation(uint32_t row, uint32_t col, const char* ptr, uint32_t length)
        : m_row(row)
        , m_col(col)
        , m_lexeme( ptr, length)
    {
    }
    std::string toString() const {
        return m_lexeme.to_string();
    }
    ADT::StringRef toStringRef() const {
        return m_lexeme;
    }
    uint32_t row() const {
        return m_row;
    }
    uint32_t col() const {
        return m_col;
    }


private:
    uint32_t       m_row;
    uint32_t       m_col;
    ADT::StringRef m_lexeme;
};