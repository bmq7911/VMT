#pragma once
#include "SymbolTable/TypeId.h"

namespace ENV {
    class BoolType : public std::enable_shared_from_this<BoolType>,public TypeId {
    public:
        
        using TypeId::TypeId;
        std::shared_ptr<TypeId> Op(TokenId TokenId)  override {
            if (TokenId::kw_not == TokenId) {
                auto p = std::enable_shared_from_this<BoolType>::shared_from_this();
                return p;
            }
            return nullptr;
        }
        std::shared_ptr<TypeId> Op(TokenId tok, std::shared_ptr<TypeId> type)  override {
            if (type.get() != this) {
                return nullptr;
            }
            else {
                const static TokenId TokenIdSupport1[] = {
                                           TokenId::kw_and,
                                           TokenId::kw_or,
                };

                for (size_t i = 0; i < sizeof(TokenIdSupport1) / sizeof(TokenIdSupport1[0]); ++i) {
                    if (TokenIdSupport1[i] == tok) {
                        if (this != type.get()) {
                            return nullptr;
                        }
                        return std::enable_shared_from_this<BoolType>::shared_from_this();
                    }
                }
                if ( tok == TokenId::kw_comma) {
                    return type;
                }
                return nullptr;
            }


        }

    private:

    };
}
