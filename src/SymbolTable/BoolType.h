#pragma once
#include "SymbolTable/TypeId.h"

namespace ENV {
    class BoolType : public std::enable_shared_from_this<BoolType>,public TypeId {
    public:
        
        using TypeId::TypeId;
        std::shared_ptr<TypeId> Op(Tag tag)  override {
            if (Tag::kw_not == tag) {
                auto p = shared_from_this();
                return p;
            }
            return getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
        }
        std::shared_ptr<TypeId> Op(Tag tag, std::shared_ptr<TypeId> type)  override {
            if (type.get() != this) {
                return getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
            }
            else {
                const static Tag tagSupport1[] = {
                                           Tag::kw_and,
                                           Tag::kw_or,
                };

                for (size_t i = 0; i < sizeof(tagSupport1) / sizeof(tagSupport1[0]); ++i) {
                    if (tagSupport1[i] == tag) {
                        if (this != type.get()) {
                            ENV::getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
                        }
                        return shared_from_this();
                    }
                }
                if (tag == Tag::kw_comma) {
                    return type;
                }
                return ENV::getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
            }


        }

    private:

    };
}
