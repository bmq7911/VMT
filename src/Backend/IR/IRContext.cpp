#include "Backend/IR/IRContext.h"

namespace IR {

    IRContext::IRContext()
        : m_currentFunc( nullptr)
    {
        m_nameAlloc = std::make_shared<NameAlloc>( );
    }
    
    IR::TypeManger& IRContext::getTypeManger() {
        return m_typeManger;
    }

    std::shared_ptr<IR::NameAlloc>  IRContext::getNameAlloc() const {
        return m_nameAlloc;
    }

    IR::Function* IRContext::getCurrentFunction() const{
        return m_currentFunc;
    }
    void          IRContext::addFunction(IR::Function* function) {
        if (nullptr != function) {
            std::string funcName = function->getFunctionName();
            m_funcmap.insert(std::make_pair(funcName, function));
            m_currentFunc = function;
        }
    }
    
	void IRContext::_IRBuilder_PushIns( IR::Instruction* ins) {
        m_currentFunc->_InsertIns(ins);
	}

    IR::Function* IRContext::_GetFunction() const {
        return m_currentFunc;
    }
}