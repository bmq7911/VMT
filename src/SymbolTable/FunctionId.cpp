#include <memory>
#include "SymbolTable/FunctionId.h"

namespace ENV {
    FunctionId::FunctionId(std::string_view name)
        : Symbol( SymbolType::kFunction, name )
    {

    }

    void   FunctionId::setEnv(std::shared_ptr<ENV::Env> env) {
        m_env = env;
    }
}
