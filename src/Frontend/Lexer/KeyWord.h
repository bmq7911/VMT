#pragma once
#include <unordered_map>
#include "Frontend/Lexer/Identifier.h"

/// �����Ҳ��ʵ������û��ʲô���õ�
/// identifier �� keyword�Ǵʷ��׶εĶ���,��û���﷨�׶ε�����ֵ��
/// �ʷ������׶�����Ҫ�ܷ��������ַ���,���������Ǳ�ʶ�� �� �ؼ���,�������ⶥ����ؼ��ֺ� ��ʶ��Ҳ�ǿ��Ե�,�����������Ӧ��
/// ����tag�����,��˷���Token Ҳ�Ǻ��ʵ�, KeyWord ֱ�Ӽ̳�Token , Indentifier Ҳֱ�Ӽ̳��� Token ����Ҳ��û��������
class KeyWord {
public:
    KeyWord();
    Tag         findTagFormStr( const char * strName);
    const char* findStrFromTag( Tag tag);
private:
    void _InsertKeyWord( const char* keywordName, Tag tag );
    void _InitKeyWordMap();
private:
    /// ����hashmap��Ϊ����
    std::unordered_map<std::string, Tag> m_keyStrTag;
    std::unordered_map<Tag, std::string> m_keyTagStr;
};