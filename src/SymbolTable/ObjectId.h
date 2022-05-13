#pragma once
#include "SymbolTable/Symbol.h"

namespace ENV {
    
    class ObjectId : public Symbol { /// 这个东西属于符号表,不属于前端
    public:
        ObjectId( std::string_view name, std::shared_ptr<TypeId> type) 
            : Symbol( SymbolType::kVariable, name )
            , m_type( type )
        {
        }


        std::shared_ptr<TypeId> getObjType() const {
            return m_type;
        }

    private:
        std::shared_ptr<TypeId> m_type;
    };

}