#pragma once
#include <unordered_map>
#include "Frontend/Lexer/Identifier.h"

/// 这个类也就实质上是没有什么作用的
/// identifier 和 keyword是词法阶段的定义,是没有语法阶段的属性值的
/// 词法分析阶段又需要能分析出各种符号,而不仅仅是标识符 和 关键字,所以在这顶定义关键字和 标识符也是可以的,但是这个类型应该
/// 是有tag定义的,因此放在Token 也是合适的, KeyWord 直接继承Token , Indentifier 也直接继承与 Token 这里也就没有类型了
class KeyWord {
public:
    KeyWord();
    Tag         findTagFormStr( const char * strName);
    const char* findStrFromTag( Tag tag);
private:
    void _InsertKeyWord( const char* keywordName, Tag tag );
    void _InitKeyWordMap();
private:
    /// 这是hashmap作为基础
    std::unordered_map<std::string, Tag> m_keyStrTag;
    std::unordered_map<Tag, std::string> m_keyTagStr;
};