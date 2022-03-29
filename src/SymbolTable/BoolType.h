#pragma once
#include "SymbolTable/TypeId.h"

namespace ENV {
    class BoolType : public std::enable_shared_from_this<BoolType>,public TypeId {
    public:
        
        using TypeId::TypeId;
        std::shared_ptr<TypeId> Op(TokenId TokenId)  override {
            if (TokenId::kw_not == TokenId) {
                auto p = shared_from_this();
                return p;
            }
            return getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
        }
        std::shared_ptr<TypeId> Op(TokenId tok, std::shared_ptr<TypeId> type)  override {
            if (type.get() != this) {
                return getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
            }
            else {
                const static TokenId TokenIdSupport1[] = {
                                           TokenId::kw_and,
                                           TokenId::kw_or,
                };

                for (size_t i = 0; i < sizeof(TokenIdSupport1) / sizeof(TokenIdSupport1[0]); ++i) {
                    if (TokenIdSupport1[i] == tok) {
                        if (this != type.get()) {
                            ENV::getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
                        }
                        return shared_from_this();
                    }
                }
                if ( tok == TokenId::kw_comma) {
                    return type;
                }
                return ENV::getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
            }


        }

    private:

    };
}
