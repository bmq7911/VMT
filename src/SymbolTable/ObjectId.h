#pragma once
#include "SymbolTable/Id.h"
#include "Frontend/AST/Expr.h"

namespace ENV {
    
    class ObjectId : public Id { /// 这个东西属于符号表,不属于前端
    public:
        ObjectId( const char *name, std::shared_ptr<TypeId> type) 
            : Id(name)
            , m_type( type )
        {}

        IdType getIdType() const {
            return IdType::kIdObject;
        }

        std::shared_ptr<TypeId> getObjType() const {
            return m_type;
        }

    private:
        std::shared_ptr<TypeId> m_type;
    };

}