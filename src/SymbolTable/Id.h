
#pragma once
#include <stdint.h>
#include "Frontend/Lexer/Token.h"

namespace ENV{
    enum IdType : uint32_t {
        kIdObject,
        kIdFunction,
        kIdType,
    };
    enum ScopeType : uint32_t {
        kGlobal,  /// ȫ��,ֻ��ʹ��const ����ʼ��
        kLocal,  /// �ֲ�
        kTemp,    /// ��ʱ( ��Ȼ�Ǿֲ��� )
    };
    /// 
    /// ������Ϊ�ܱ���¼�����ű�Ķ�������Ϊid(or symbol),����Ҳ��һ��Symbol
	class Id{
    public:
        Id( const char* name)
            :m_name(name)
        {

        }
        virtual IdType getIdType() const = 0;
        std::string const& getIdName() const {
            return m_name;
        }
    private:
        ScopeType   m_scopeType;
        std::string m_name;
	};
	
}