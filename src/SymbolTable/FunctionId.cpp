#include <memory>
#include "SymbolTable/FunctionId.h"

namespace ENV {
    FunctionId::FunctionId(const char* name)
        :Id( name )
    {}
    IdType FunctionId::getIdType() const {
        return IdType::kIdFunction;
    }
    void   FunctionId::setEnv(std::shared_ptr<ENV::Env> env) {
        m_env = env;
    }
}
