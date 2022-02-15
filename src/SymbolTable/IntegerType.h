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
        std::shared_ptr<TypeId> Op(Tag tag)  override {
            const static Tag tagSupport[] = { Tag::kw_plus,
                                              Tag::kw_plusplus,
                                              Tag::kw_minus,
                                              Tag::kw_minusminus,};
            for (size_t i = 0; i < sizeof(tagSupport) / sizeof(tagSupport[0]); ++i) {
                if (tag == tagSupport[i])
                    return shared_from_this();
            }
            return getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
        }
        std::shared_ptr<TypeId> Op(Tag tag, std::shared_ptr<TypeId> type)  override {
            if (type.get() != this) {
                return getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
            }
            else {
                const static Tag tagSupport1[] = {
                                           Tag::kw_equal,
                                           Tag::kw_plus,
                                           Tag::kw_minus,
                                           Tag::kw_plusequal,
                                           Tag::kw_minusequal,
                                           Tag::kw_star,
                                           Tag::kw_starequal,
                                           Tag::kw_starstar,
                                           Tag::kw_slash,
                                           Tag::kw_slashequal,
                                           Tag::kw_percent,
                                           Tag::kw_percentequal,
                                           Tag::kw_lessless,
                                           Tag::kw_lesslessequal,
                                           Tag::kw_greatergreater,
                                           Tag::kw_greatergreaterequal,
                                           Tag::kw_bitand,
                                           Tag::kw_bitor,
                                           Tag::kw_bitcompl,
                };

                const static Tag tagSupport2[]={
                                           Tag::kw_less,
                                           Tag::kw_lessequal,
                                           Tag::kw_spaceship,
                                           Tag::kw_greater,
                                           Tag::kw_greaterequal,
                };
                for (size_t i = 0; i < sizeof(tagSupport1) / sizeof(tagSupport1[0]); ++i) {
                    if (tagSupport1[i] == tag) {
                        if (this != type.get()) {
                            return ENV::getTopEnv()->getBasicType(ENV::BasicType::kArbitrary);
                        }
                        return shared_from_this();
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
                if (tag == Tag::kw_comma) {
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

