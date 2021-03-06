#pragma once
#include <string>
#include "Backend/IR/Users.h"
#include "ADT/dlink.h"
namespace IR{
    class Type;
    class Instruction;
    class Constant;

	/// <summary>
	/// value描述的时一个值,一个数据,可能时常量也可能时变量
	/// </summary>
	class Value : public ADT::d_link<Value>{
	public:
        enum ValueTy {
#define HANDLE_VALUE
#include "Backend/IR/Value.def"
#undef HANDLE_VALUE
        };

        /// <summary>
        ///  Value 被赋值的语句
        /// </summary>
        
        Value(const char* name, Type const* type, Instruction* ins);
        Value* clone();

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

        virtual std::string getValueName() const {
            if (0 == m_nameIndex)
                return m_name;
            else
                return m_name + '@' + std::to_string(m_nameIndex);
        }
        
        const std::string& getOriginName() const {
            return m_name;
        }
        void setInstruction( Instruction* ins) {
            m_ins = ins;
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
        void setNameIndex( uint32_t index ) {
            
        }
    protected:

    protected:
        std::string  m_name;       /// value name
        const Type*  m_type;       /// value type
        Instruction* m_ins;        /// the define ins
        uint32_t  m_bLocal    : 1;
        uint32_t  m_bConstant : 1;
        uint32_t  m_bVolatile : 1;
        uint32_t  m_bStatic   : 1;
        uint32_t  m_nameIndex;
        Users     m_users;
	};

}