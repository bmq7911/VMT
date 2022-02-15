#include "ADT/StringRef.h"

namespace ADT {

    std::string StringRef::to_string() const {
        if (nullptr == m_ptr || 0 == m_length) {
            return std::string("");
        }
        else {
        
            return std::string(m_ptr, m_length);
        }
    }
}
