#include "SymbolTable/Env.h"
#include "SymbolTable/FunctionId.h"
#include "SymbolTable/ObjectId.h"
#include "SymbolTable/TypeId.h"

namespace ENV {


    Env::Env() {
    }
    Env::Env(std::shared_ptr<Env> n) {
        m_prev = n; /// 可以把一个 shared_ptr 赋值给 weak_ptr,但是不会引起shared_ptr 之中对象的引用计数增加
    }
    std::shared_ptr<Env> Env::getParent() {
        return m_prev;
    }

    void Env::mount(std::shared_ptr<ENV::Env> env) {
        m_prev = env;
    }
    void Env::unmount() {
        m_prev = nullptr;
    }


    bool Env::put(std::shared_ptr<ENV::Symbol> symbol) {
        if (!symbol)
            return false;
        auto type = symbol->getSymbolType();
        auto iter = m_maps.find(type);
        if (iter == m_maps.end()) {
            m_maps.insert(std::make_pair(type, std::unordered_map<std::string_view, std::shared_ptr<ENV::Symbol>>{}));
            iter = m_maps.find(type);
        }
        auto kter = iter->second.find(symbol->getSymbolName());
        if (kter != iter->second.end()) {
            return false;
        }
        else {
            iter->second.insert(std::make_pair(symbol->getSymbolName(), symbol));
            return true;
        }
    }
    
    std::shared_ptr<ENV::Symbol> Env::find(std::string_view const& view, ENV::SymbolType type) {
        auto iter = m_maps.find(type);
        if (iter == m_maps.end()) {
            auto parent = getParent();
            if (parent)
                return parent->find(view, type);
            return nullptr;
        }
        else {
            auto kter = iter->second.find(view);
            if (kter == iter->second.end()) {
                auto parent = getParent();
                if (parent)
                    return parent->find(view, type);
                return nullptr;
            }
            return kter->second;
        }
    }

    bool Env::put(std::string const& str, IR::Value* v) {
        auto iter = m_values.find(str);
        if (iter != m_values.end()) {
            return false;
        }
        else {
            auto pair = m_values.insert(std::make_pair(str,v));
            return pair.second;
        }
    }

    IR::Value* Env::find(std::string const&str) {
        auto iter = m_values.find(str);
        if (iter != m_values.end()) {
            return iter->second;
        }
        return nullptr;
    }
}

