#pragma once
#include <memory>
#include "Frontend/Lexer/Lexer.h"
#include "Frontend/Lexer/File.h"

class FileLexer : public Lexer {
public:
    FileLexer(const char* strPath) 
        : m_tokenStart( -1 )
        , m_scanIndex( -1)
        , m_lineNumber( 1)
        , m_colNumber( -1 )
    {
        m_file = std::make_shared<File>( strPath );
    }
    void  startToken() override {
        m_tokenStart = m_scanIndex;
    }

    Token genToken(TokenId tokid) {
        std::string_view source_str_view = m_file->getSourceRef();
        std::string_view lexme( source_str_view.data() + m_tokenStart, m_scanIndex - m_tokenStart );
        Token tok;
        tok.m_tokenId = tokid;
        tok.m_location = _GetFileLocation();
        return tok;
    }
    std::string_view genLexeme( ) override {
        std::string_view source_str_view = m_file->getSourceRef();
        return std::string_view( source_str_view.data() + m_tokenStart, m_scanIndex - m_tokenStart );
    }
    void nextLine() {
        m_lineNumber++;
        m_colNumber = 0;
    }
private:
    FileLocation _GetFileLocation()  const{
        std::string_view source_str_view = m_file->getSourceRef();
        FileLocation location( m_lineNumber,
                               m_colNumber + m_tokenStart - m_scanIndex,
                               source_str_view.data() + m_tokenStart,
                               m_scanIndex - m_tokenStart);
        return location;
    }
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
private:
    size_t m_tokenStart;
    size_t m_scanIndex;
    size_t m_lineNumber;
    size_t m_colNumber;
    std::shared_ptr<File> m_file;
};
