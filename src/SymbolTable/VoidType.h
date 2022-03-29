#pragma once

#include "SymbolTable/TypeId.h"

namespace ENV {
    class VoidType : public std::enable_shared_from_this<VoidType>, public TypeId {
    public:
        using TypeId::TypeId;
        std::shared_ptr<TypeId> Op(TokenId tag)  override {
            return getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
        }
        std::shared_ptr<TypeId> Op(TokenId tag, std::shared_ptr<TypeId> type)  override {
            if (tag == TokenId::kw_comma) {
                return type;
            }
            return ENV::getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
        }

        
    };
}

