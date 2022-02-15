#pragma once
#include <string>
#include "Frontend/Lexer/Tag.h"
#include "Frontend/Lexer/FileLocation.h"

class Token { /// ���token ��Ϣ̫����,�������ǲ�����
public:
    Token() 
        :m_tag(Tag::unknown)
    {}
	Token(Tag t) 
    { 
        m_tag = t;
	}
    operator bool() const {
        return Tag::unknown != m_tag;
    }
    bool match(Tag tag) const {
        return tag == m_tag;
    }
	std::string toString() const {
        return m_location.toString();
	}
    ADT::StringRef toStringRef() const {
        return m_location.toStringRef();
    }
    Tag getTag() const {
        return m_tag;
    }
public:
	Tag  m_tag;
    FileLocation m_location;
};
