#pragma once 
#include "SymbolTable/Id.h"
#include "SymbolTable/TopEnv.h"
#include <memory>

namespace ENV {
    class TopEnv;
    std::shared_ptr<TopEnv> getTopEnv();
    class TypeId : public Id{ /// Type 也有作用域,但是关键字是没作用域的把
    public:
        enum OpCheck {
            kOpSupport     = 0,
            kOpUnsupportOp = 1,
            kOpErrorType   = 2,

        };
        uint32_t m_width;
        uint32_t m_align;

        int width = 0;          // width is used for storage allocation
        /// 都错了
        //static std::shared_ptr<TypeId> Void, Bool, I8, I16, I32, I64, UI8, UI16, UI32, UI64, F32, F64;
    public:
        IdType getIdType() const override final {
            return IdType::kIdType;
        }

        TypeId(char  const * tok)
            : Id(tok)
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
        /// 检查是否支持 a op b( 二元操作) 不支持更高元操作

    };
}


