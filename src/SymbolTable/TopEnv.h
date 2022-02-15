#pragma once
#include "SymbolTable/Env.h"

namespace ENV {
    class TypeId;
    enum BasicType : uint32_t {
        kVoid,
        kBool,
        kI8,
        kUI8,
        kI16,
        kUI16,
        kI32,
        kUI32,
        kI64,
        kUI64,
        kF32,
        kF64,
        kArbitrary,
    };

    class TopEnv : public Env {
    public:
        TopEnv();
        static std::shared_ptr<ENV::TypeId> getBasicType(const char* name);
        static std::shared_ptr<ENV::TypeId> getBasicType(BasicType type);
        
    };
    std::shared_ptr<TopEnv> getTopEnv();



    
}