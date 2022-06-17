#include "Backend/IR/Function.h"
#include "Backend/IR/IRContext.h"
#include "Backend/IR/Value.h"
#include "Backend/IR/Instruction.h"
#include "Backend/IR/Type.h"
#include "Backend/IR/BasicBlock.h"


namespace IR {

    Function::Function() {
        
    }
    Function::Function(const char* name, FunctionType const* funcType)
        : m_name(name)
        , m_type(funcType)
    {
        m_functionScope         = std::make_shared<Scope>();
        m_constantTable = std::make_shared<ConstantTable>();
        m_labelTable    = std::make_shared<LabelTable>();
    }

    Function::Function(char const* name, FunctionType const* funcType, std::shared_ptr<Scope> up)
        : m_name(name)
        , m_type(funcType)
    {
        m_functionScope = std::make_shared<Scope>(up);
        m_constantTable = std::make_shared<ConstantTable>();
        m_labelTable    = std::make_shared<LabelTable>();
    }

    void Function::addArgs(Value* args) {
        //FunctionType const* type = static_cast<FunctionType const*>(m_type);
        //size_t i = m_args.size();
        //if (i < type->sizeParamsType()) {
        //    m_args.push_back(args);
        //}
    }

    std::string const& Function::getFunctionName() const {
        return m_name;
    }


    Label* Function::findLabel(std::string const& label) const {
        return m_labelTable->findLabel(label);
    }
    bool   Function::insertLabel(std::string const& name, Label* label) {
        if (nullptr != label)
            return m_labelTable->insertLabel(name, label);
        return false;
    }

    void   Function::insertValue(Value* value) {
        std::string name = value->getValueName();
        m_functionScope->insertValue(name, value);
    }
    std::shared_ptr<Scope> Function::getFunctionScope() const {
        return m_functionScope;
    }

    FunctionType const* Function::getFunctionType() const {
        return m_type;
    }

    size_t Function::getArgsSize() const {
        return m_args.size();
    }

    Value* Function::getArgsAt(size_t i) const {
        return m_args.at(i);
    }

    uint32_t Function::verifyFunction() {
        getFlowGraphs();
        /// 代码结构体调整,将结构转化为SSA形式
        return 0;
    }
    
    std::shared_ptr<FlowGraphs> Function::getFlowGraphs() {
        if (!m_controlFlowGraphs) {
            m_controlFlowGraphs = FlowGraphs::makeFlowGraphs(this);
        }
        return m_controlFlowGraphs;
    }
    Instruction* Function::begin() {
        return m_instructions.begin();
    }

    Instruction* Function::end() {
        return m_instructions.end();
    }

    Instruction const* Function::begin() const {
        return m_instructions.begin();
    }

    Instruction const* Function::end() const {
        return m_instructions.end( );
    }
    void Function::_InsertIns(Instruction* ins) {
        m_instructions.push_back(ins);
    }
    
    Instruction* Function::first() {
        return m_instructions.first();
    }
    Instruction const* Function::first() const {
        return m_instructions.first();
    }
    Instruction* Function::last() {
        return m_instructions.last();
    }
    Instruction const* Function::last() const {
        return m_instructions.last();
    }
    

}