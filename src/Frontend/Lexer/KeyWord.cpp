#include "Frontend/Lexer/KeyWord.h"
#include "Frontend/Lexer/Tag.h"

KeyWord::KeyWord() {
    _InitKeyWordMap();
}

Tag  KeyWord::findTagFormStr(const char * strName) {
    auto iter = m_keyStrTag.find(std::string(strName));
    if (iter != m_keyStrTag.end()) {
        return iter->second;
    }
    return Tag::unknown;
}

const char*  KeyWord::findStrFromTag(Tag tag) {
    auto iter = m_keyTagStr.find(tag);
    if (iter != m_keyTagStr.end()) {
        return iter->second.c_str();
    }
    return nullptr;
}

void KeyWord::_InsertKeyWord(const char* keywordName, Tag tag) {
    m_keyStrTag.insert(std::pair(std::string(keywordName), tag));
    m_keyTagStr.insert(std::pair(tag,std::string(keywordName) ));
}
 
void KeyWord::_InitKeyWordMap() {

#define DEFINE_KEYWORD
#include "Frontend/Lexer/KeyWord.def"
#undef DEFINE_KEYWORD

}

