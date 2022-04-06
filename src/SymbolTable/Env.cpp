#include "SymbolTable/Env.h"
#include "SymbolTable/FunctionId.h"
#include "SymbolTable/ObjectId.h"
#include "SymbolTable/TypeId.h"

namespace ENV {
    int Env::staticEnvIndex = 0;


    Env::Env(std::shared_ptr<Env> n) {
        envIndex = Env::staticEnvIndex++;
        m_prev = n; /// 可以把一个 shared_ptr 赋值给 weak_ptr,但是不会引起shared_ptr 之中对象的引用计数增加
    }
    std::shared_ptr<Env> Env::getParent() {
        return m_prev;
    }
    void Env::put( std::string const &str, std::shared_ptr<ENV::ObjectId> id) {
        m_ObjectTable.insert(std::pair(str, id));
    }
    
    void Env::put(std::string const &str, std::shared_ptr<ENV::FunctionId> id) {
        m_FunctionTable.insert(std::pair(str, id));
    }
    
    void Env::put(std::string const &str, std::shared_ptr<ENV::TypeId> id) {
        m_TypeTable.insert(std::pair(str, id));
    }
    
    std::shared_ptr<ENV::ObjectId> Env::getObjectId(std::string const& w) {
        for (std::shared_ptr<Env> e = shared_from_this(); e; e = e->getParent()) {
            auto iter = e->m_ObjectTable.find(w);
            if (iter != e->m_ObjectTable.end()) {
                return iter->second;
            }
        }
        return nullptr;
    }
    std::shared_ptr<ENV::FunctionId> Env::getFunctionId(std::string const& w) {
        for (std::shared_ptr<Env> e = shared_from_this(); e; e = e->getParent()) {
            auto iter = e->m_FunctionTable.find(w);
            if (iter != e->m_FunctionTable.end()) {
                return iter->second;
            }
        }
        return nullptr;

    }
    std::shared_ptr<ENV::TypeId>     Env::getTypeId(std::string const& w) {
        for (std::shared_ptr<Env> e = shared_from_this(); e; e = e->getParent()) {
            auto iter = e->m_TypeTable.find(w);
            if (iter != e->m_TypeTable.end()) {
                return iter->second;
            }
        }
        return nullptr;

    
    }

           

           
    void Env::put(std::string const & str, std::shared_ptr<ENV::Symbol> i, ENV::SymbolType type) {
        switch (type) {
        case ENV::SymbolType::kVariable: {
            std::shared_ptr<ENV::ObjectId> id = std::static_pointer_cast<ENV::ObjectId>( i );
            put(str, id);
        }break;
        case ENV::SymbolType::kFunction: {
            std::shared_ptr<ENV::FunctionId> id = std::static_pointer_cast<ENV::FunctionId>( i );
            put(str, id);
        }break;
        case ENV::SymbolType::kType: {
            std::shared_ptr<ENV::TypeId> id = std::static_pointer_cast<ENV::TypeId>( i );
            put(str, id);
        }break;
        default:
            break;
        }
    }

    uint32_t Env::getEnvIndex() const {
        return envIndex;
    }

    std::shared_ptr<ENV::Symbol> Env::get(std::string const& w, ENV::SymbolType type) {
        switch (type) {
        case ENV::SymbolType::kVariable: {
            for (std::shared_ptr<Env> e = shared_from_this(); e; e = e->getParent()) {
                auto iter = e->m_ObjectTable.find(w);
                if (iter != e->m_ObjectTable.end()) {
                    return iter->second;
                }
            }
        }break;
        case ENV::SymbolType::kType: {
            for (std::shared_ptr<Env> e = shared_from_this(); e; e = e->getParent()) {
                auto iter = e->m_TypeTable.find(w);
                if (iter != e->m_TypeTable.end()) {
                    return iter->second;
                }
            }
        } break;
        case ENV::SymbolType::kFunction: {
            for (std::shared_ptr<Env> e = shared_from_this(); e; e = e->getParent()) {
                auto iter = e->m_FunctionTable.find(w);
                if (iter != e->m_FunctionTable.end()) {
                    return iter->second;
                }
            }
        }break;
        default:
            break;
        }
        return nullptr;
    }
}

