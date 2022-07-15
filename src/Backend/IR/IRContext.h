#pragma once
#include "Backend/IR/Function.h"
#include "Backend/IR/Type.h"

namespace IR {
	
	class IRContext {
	public:
        IRContext();
        IRContext(IRContext const &) = delete;
        IRContext(IRContext &&) = delete;
        IRContext & operator=(IRContext const&) = delete;
        IRContext& operator=(IRContext &&) = delete;

        IR::TypeManger& getTypeManger();
        IR::Function*   getCurrentFunction() const;
            
        void            addFunction(IR::Function* function );
    private:
		friend class IRBuilder;
		void _IRBuilder_PushIns( IR::Instruction * );
        IR::Function* _GetFunction() const;
        
	private:
        IR::TypeManger        m_typeManger;
        std::map<std::string, IR::Function*> m_funcmap;
        IR::Function*         m_currentFunc;
    };
}