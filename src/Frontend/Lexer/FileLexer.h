#pragma once
#include <memory>
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/Lexer/File.h"

class FileLexer : public Lexer {
public:
private:
    int32_t _Readch() {
        m_scanIndex++;
        m_colNumber++;
        std::string_view view = m_file->getSourceRef();
        if (m_scanIndex < view.length()) {
            return m_file->getSourceRef().at(m_scanIndex);
        }
        return EOF;
    }
    Token  _GenToken(TokenId id) {
        
    }
    size_t _GetLineNumber() const {
        return m_lineNumber;
    }
    size_t _GetColNumber() const {
        return m_colNumber;
    }
private:
    size_t m_scanIndex;
    size_t m_lineNumber;
    size_t m_colNumber;
    std::shared_ptr<File> m_file;
};
