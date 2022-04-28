#pragma once
#ifdef min
#undef min
#undef max
#endif ///min
#include "SymbolTable/TopEnv.h"
#include "SymbolTable/TypeId.h"

namespace ENV {
	template<typename _T>
    class IntegerType : public std::enable_shared_from_this<IntegerType<_T>> ,public TypeId {
    public:
        using HostType = _T;
        IntegerType(  const char*  tok )
            : TypeId( tok)
            , m_min (std::numeric_limits<_T>::min())
            , m_max (std::numeric_limits<_T>::max())
            , m_align( alignof(_T))
        {
            
        }
        /// v1 op v2
        std::shared_ptr<TypeId> Op(TokenId tag)  override {
            const static TokenId tagSupport[] = { TokenId::kw_plus,
                                              TokenId::kw_plusplus,
                                              TokenId::kw_minus,
                                              TokenId::kw_minusminus,};
            for (size_t i = 0; i < sizeof(tagSupport) / sizeof(tagSupport[0]); ++i) {
                if (tag == tagSupport[i])
                    return std::enable_shared_from_this<IntegerType<_T>>::shared_from_this();
            }
            return getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
        }
        std::shared_ptr<TypeId> Op(TokenId tag, std::shared_ptr<TypeId> type)  override {
            if (type.get() != this) {
                return getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
            }
            else {
                const static TokenId tagSupport1[] = {
                                           TokenId::kw_equal,
                                           TokenId::kw_plus,
                                           TokenId::kw_minus,
                                           TokenId::kw_plusequal,
                                           TokenId::kw_minusequal,
                                           TokenId::kw_star,
                                           TokenId::kw_starequal,
                                           TokenId::kw_starstar,
                                           TokenId::kw_slash,
                                           TokenId::kw_slashequal,
                                           TokenId::kw_percent,
                                           TokenId::kw_percentequal,
                                           TokenId::kw_lessless,
                                           TokenId::kw_lesslessequal,
                                           TokenId::kw_greatergreater,
                                           TokenId::kw_greatergreaterequal,
                                           TokenId::kw_bitand,
                                           TokenId::kw_bitor,
                                           TokenId::kw_bitcompl,
                };

                const static TokenId tagSupport2[]={
                                           TokenId::kw_less,
                                           TokenId::kw_lessequal,
                                           TokenId::kw_spaceship,
                                           TokenId::kw_greater,
                                           TokenId::kw_greaterequal,
                };
                for (size_t i = 0; i < sizeof(tagSupport1) / sizeof(tagSupport1[0]); ++i) {
                    if (tagSupport1[i] == tag) {
                        if (this != type.get()) {
                            return ENV::getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
                        }
                        return std::enable_shared_from_this<IntegerType<_T>>::shared_from_this();
                    }
                }
                for (size_t i = 0; i < sizeof(tagSupport2) / sizeof(tagSupport2[0]); ++i) {
                    if (tagSupport2[i] == tag) {
                        if (this != type.get()) {
                            return ENV::getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
                        }
                        return ENV::getTopEnv()->getBasicType(ENV::BasicType::kBool);
                    }
                }
                if (tag == TokenId::kw_comma) {
                    return type;
                }
                return ENV::getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
            }


        }



    private:
        HostType m_min;
        HostType m_max;
        uint32_t m_align;
        
    };

}

