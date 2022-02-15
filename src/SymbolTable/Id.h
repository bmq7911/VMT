
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
        kGlobal,  /// 全局,只能使用const 来初始化
        kLocal,  /// 局部
        kTemp,    /// 零时( 必然是局部的 )
    };
    /// 
    /// 我们认为能被记录到符号表的东西被称为id(or symbol),类型也是一种Symbol
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