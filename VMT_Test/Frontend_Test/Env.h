#pragma once 
#include <map>
#include <memory>
#include <unordered_map>

#include "Backend/IR/Value.h"

namespace ENV {

    class ValueList {
    public:
        ValueList() 
            : m_values( nullptr )
        {}

        IR::Value* getValue() const {
            return m_values;
        }
        void setValue(IR::Value* value) {
            if (nullptr == m_values) {
                m_values = value;
                return;
            }
            m_values->insert_front(value);
            return;
        }
    private:
        IR::Value* m_values;
    };

    

    
    
}
