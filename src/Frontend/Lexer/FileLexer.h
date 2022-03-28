#pragma once
#include <memory>
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/Lexer/File.h"

class FileLexer : public Lexer {
public:
    Token scan( ) override {
        char ch = char(0);
        /// 1. 处理掉空格和'\t'
        do {
            int32_t t = _Readch();
            if (t == EOF) {
                return _GenToken(TokenId::kw_eof);
            }
            else if( t == ' '|| t == '\t') {
                continue;
            }
            else {
                ch = t;
                break;
            }
        } while ( true );
        /// 2. 处理数字的情况
        if (std::isdigit(ch)) {
            
        }
        else if (std::isalpha(ch) || '_' == ch) {
            
        }
        else {
            
        }

    }
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
