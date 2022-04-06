#pragma once 
#include <map>
#include <memory>
#include "SymbolTable/Symbol.h"

namespace ENV {
    class ObjectId;
    class TypeId;
    class FunctionId;
    

    class Env : public std::enable_shared_from_this<Env> {
    public:
        Env(std::shared_ptr<Env> n);
        std::shared_ptr<Env> getParent();
        void put(std::string const &str, std::shared_ptr<ENV::ObjectId> id);
        void put(std::string const &str, std::shared_ptr<ENV::FunctionId> id);
        void put(std::string const &str, std::shared_ptr<ENV::TypeId> id);
        std::shared_ptr<ENV::ObjectId>   getObjectId( std::string const& str);
        std::shared_ptr<ENV::FunctionId> getFunctionId(std::string const& str);
        std::shared_ptr<ENV::TypeId>     getTypeId(std::string const& str);
        void put(std::string const & str, std::shared_ptr<ENV::Symbol> i, ENV::SymbolType type);
        uint32_t getEnvIndex() const;
        std::shared_ptr<ENV::Symbol> get(std::string const& w, ENV::SymbolType type);

    private:
        std::shared_ptr<Env> m_prev; /// 连接到前一个符号表,但是前一个符号表不会直接指向内层符号表
        static int staticEnvIndex;
        int envIndex;
    private:
        std::map<std::string, std::shared_ptr<ENV::ObjectId> > m_ObjectTable;
        std::map<std::string, std::shared_ptr<ENV::TypeId> >   m_TypeTable;
        std::map<std::string, std::shared_ptr<ENV::FunctionId>>m_FunctionTable;
    };

    
}
