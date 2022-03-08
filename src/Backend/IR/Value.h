#pragma once
#include <string>
#include "Backend/IR/Users.h"

namespace IR{
    class Type;
    class Instruction;
    class Constant;

	/// <summary>
	/// value描述的时一个值,一个数据,可能时常量也可能时变量
	/// </summary>
	class Value{
	public:
        enum ValueTy {
#define HANDLE_VALUE
#include "Backend/IR/Value.def"
#undef HANDLE_VALUE
        };
        Value(const char* name, Type const* type, Instruction* ins);

        /*
        bool isLagal() const {
            return nullptr != m_type && !m_name.empty( );
        }
        */
        bool isConstant() const{
            return m_bConstant;
        }

        bool isVolatile() const {
            return m_bVolatile;
        }

        bool isStatic() const {
            return m_bStatic;
        }

        bool isLocal() const {
            return m_bLocal;
        }

        const Type* getType() const {
            return m_type;
        }

        const std::string& getValueName() const {
            return m_name;
        }

        Instruction* getInstruction() {
            return m_ins;
        }

        Instruction const* getInstruction() const {
            return m_ins;
        }
        
        
        
        void addUser(Value* v);
        
        Users const& getUsers() const;
        
        virtual std::string emitStr() const {
            return m_name;
        }
    protected:

    protected:
        std::string  m_name;
        const Type*  m_type;
        Instruction* m_ins;
        uint32_t  m_bLocal    : 1;
        uint32_t  m_bConstant : 1;
        uint32_t  m_bVolatile : 1;
        uint32_t  m_bStatic   : 1;
        Users     m_users;
	};

}