#pragma once
#include <string>
#include <string_view>
#include "Frontend/Lexer/TokenId.h"
#include "Frontend/Lexer/FileLocation.h"

class Token { /// 这个token 信息太少了,按道理是不够的
public:
    Token() 
        :m_tokenId(TokenId::kw_Unknown)
    {}
	Token(TokenId t) 
    { 
        m_tokenId = t;
	}
    operator bool() const {
        return TokenId::kw_Unknown != m_tokenId;
    }
    bool match(TokenId tag) const {
        return tag == m_tokenId;
    }
	std::string toString() const {
        return m_location.toString();
	}
    std::string_view toStringRef() const {
        return m_location.getStringView( );
    }
    TokenId getTag() const {
        return m_tokenId;
    }
public:
	TokenId  m_tokenId;
    FileLocation m_location;
};
