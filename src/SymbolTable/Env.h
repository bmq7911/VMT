#pragma once 
#include <map>
#include <memory>
#include <unordered_map>

#include "SymbolTable/Symbol.h"
#include "Backend/IR/Value.h"

namespace ENV {
    class ObjectId;
    class TypeId;
    class FunctionId;
    
    // 这个东西不应该是封闭的类
    class Env : public std::enable_shared_from_this<Env> {
    public:
        Env();
        Env(std::shared_ptr<Env> n);
        std::shared_ptr<Env> getParent();

        void mount(std::shared_ptr<ENV::Env>);
        void unmount();
        bool put(std::shared_ptr<ENV::Symbol> symbol);
        std::shared_ptr<ENV::Symbol> find(std::string_view const& view, ENV::SymbolType type);
        bool put(std::string const& str, IR::Value* v);
        IR::Value* find(std::string const& view);

    private:
        std::shared_ptr<Env> m_prev; /// 连接到前一个符号表,但是前一个符号表不会直接指向内层符号表
    private:
        std::map<std::string, std::shared_ptr<ENV::ObjectId> >  m_ObjectTable;
        std::map<std::string, std::shared_ptr<ENV::TypeId> >    m_TypeTable;
        std::map<std::string, std::shared_ptr<ENV::FunctionId>> m_FunctionTable;
        std::map<std::string, IR::Value* >                      m_values;
        std::map<ENV::SymbolType, std::unordered_map<std::string_view, std::shared_ptr<ENV::Symbol>> > m_maps;
    };

    
}
