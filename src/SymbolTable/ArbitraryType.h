#pragma once
#include "SymbolTable/TypeId.h"
#include "SymbolTable/TopEnv.h"

namespace ENV{
    class ArbitraryType : public TypeId {
    public:
        using TypeId::TypeId;

        std::shared_ptr<TypeId> Op(Tag tag)  override{
            std::shared_ptr<TopEnv> topEnv = getTopEnv();
            return topEnv->getBasicType(  BasicType::kArbitrary);
        }
        std::shared_ptr<TypeId> Op(Tag tag, std::shared_ptr<TypeId> type)  override{
            return Op(tag);
        }

    };
}