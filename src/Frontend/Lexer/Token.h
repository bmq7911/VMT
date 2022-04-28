#pragma once
#include <string>
#include <string_view>
#include "Frontend/Lexer/TokenId.h"
#include "Frontend/Lexer/FileLocation.h"

class Token { /// 这个token 信息太少了,按道理是不够的
public:
    Token() 
        :m_tokenId(TokenId::kw_Unknown)
        , m_location()
    {}
	Token(TokenId t) { 
        m_tokenId = t;
	}
    Token(Token  const& tok) 
        : m_tokenId( tok.m_tokenId)
        , m_location( tok.m_location)
    {}
    Token& operator=(Token const& tok) {
        if (this != &tok) {
            m_tokenId = tok.m_tokenId;
            m_location = tok.m_location;
        }
        return *this;
    }
    Token(Token&& tok)
        : m_tokenId( std::move(tok.m_tokenId ))
        , m_location( std::move(tok.m_location))
    {}
    Token& operator=(Token&& tok) {
        if (this != &tok) {
            m_tokenId = std::move(tok.m_tokenId);
            m_location = std::move(tok.m_location);
        }
        return *this;

    }

    operator bool() const {
        return TokenId::kw_Unknown != m_tokenId;
    }
    template<typename ... T>
    bool match(T ... id) const;

    bool match(TokenId tag) const {
        return tag == m_tokenId;
    }
    template<typename ... T>
    bool match(TokenId head, T ... id) const {
        return match( head ) ? true : match( id ... );
    }
    template<typename ... T>
    bool not_match(T ... id) const;
    bool not_match(TokenId id) const {
        return m_tokenId != id;
    }
    template<typename ... T>
    bool not_match(TokenId head, T ... id) const {
        return not_match(head) ? true : not_match(id ...);
    }
	std::string toString() const {
        return m_location.toString();
	}
    std::string_view toStringRef() const {
        return m_location.getStringView( );
    }
    TokenId getTokenId() const {
        return m_tokenId;
    }
    FileLocation& getLocation() {
        return m_location;
    }
public:
	TokenId  m_tokenId;
    FileLocation m_location;
};
