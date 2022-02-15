#pragma once
#include "SymbolTable/Id.h"
#include "SymbolTable/Env.h"

namespace ENV {
    class FunctionId : public Id {
    public:
        FunctionId( const char* name);
        IdType getIdType() const override final;
        void   setEnv(std::shared_ptr<ENV::Env> );

    private:
        std::shared_ptr<ENV::Env> m_env;
    };
}