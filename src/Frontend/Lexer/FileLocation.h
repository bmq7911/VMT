#pragma once
#include <string_view>
class FileLocation {
    friend class Lexer;
public:
    explicit FileLocation() 
        : m_row(0)
        , m_col(0)
        , m_lexeme( )
        , m_fileId( 0 )
    {
    }
    explicit FileLocation(uint32_t row, uint32_t col, const char* ptr, uint32_t length)
        : m_row(row)
        , m_col(col)
        , m_lexeme( ptr, length)
        , m_fileId(0)
    {
    }
    explicit FileLocation(FileLocation const& location)
        : m_row( location.m_row)
        , m_col( location.m_col)
        , m_lexeme( location.m_lexeme)
        , m_fileId( location.m_fileId )
    {}
    FileLocation& operator=(FileLocation const& location) {
        if (this != &location) {
            m_row = location.m_row;
            m_col = location.m_col;
            m_lexeme = location.m_lexeme;
            m_fileId = location.m_fileId;
        }
        return *this;
    }
    FileLocation(FileLocation&& location) 
        : m_row(location.m_row)
        , m_col(location.m_col)
        , m_lexeme(location.m_lexeme)
        , m_fileId(location.m_fileId)
    {}
    FileLocation& operator=(FileLocation&& location) {
        if (this != &location) {
            m_row = location.m_row;
            m_col = location.m_col;
            m_lexeme = location.m_lexeme;
            m_fileId = location.m_fileId;
        }
        return *this;
    }

    std::string toString() const {
        return std::string( m_lexeme.data(), m_lexeme.length());
    }
    std::string_view getStringView() const {
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
    std::string_view m_lexeme;
    uint32_t       m_fileId; /// 0是不存在,1为终端, >1为文件
};