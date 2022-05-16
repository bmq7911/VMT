#pragma once 
#include "Frontend/Lexer/TokenId.h"
#include "SymbolTable/Symbol.h"
#include <memory>

namespace ENV {
    class TopEnv;
    std::shared_ptr<TopEnv> getTopEnv();
    class TypeId : public Symbol{ /// Type Ҳ��������,���ǹؼ�����û������İ�
    public:
        enum OpCheck {
            kOpSupport     = 0,
            kOpUnsupportOp = 1,
            kOpErrorType   = 2,
        };

        uint32_t m_width;
        uint32_t m_align;

        int width = 0;          // width is used for storage allocation
        /// ������
        //static std::shared_ptr<TypeId> Void, Bool, I8, I16, I32, I64, UI8, UI16, UI32, UI64, F32, F64;
    public:
        TypeId( std::string_view name )
            : Symbol( SymbolType::kType ,name)
        {
        }

        bool operator==(TypeId const & t) const {
            return this == &t;
        }

        bool operator != (TypeId const & t) const {
            return !(*this == t);
        }

        virtual std::shared_ptr<TypeId> Op(TokenId tag)  = 0;
        virtual std::shared_ptr<TypeId> Op(TokenId tag, std::shared_ptr<TypeId> type)  = 0;
        /// ����Ƿ�֧�� a op b( ��Ԫ����) ��֧�ָ���Ԫ����

    };
}


