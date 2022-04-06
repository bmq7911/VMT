#pragma once
#include "SymbolTable/Symbol.h"
#include "SymbolTable/Env.h"

namespace ENV {
    class FunctionId : public Symbol {
    public:
        FunctionId( std::string_view );
        void   setEnv(std::shared_ptr<ENV::Env> );

    private:
        std::shared_ptr<ENV::Env> m_env;
    };
}