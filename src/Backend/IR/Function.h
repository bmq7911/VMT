#pragma once
#include <map>
#include <vector>
#include <string>
#include <list>

#include "Backend/IR/Scope.h"
#include "Backend/IR/NameAlloc.h"
#include "Backend/IR/ConstantTable.h"
#include "Backend/IR/LabelTable.h"
#include "Backend/IR/FlowGraphs.h"
#include "Backend/IR/Variable.h"

namespace IR {

    class FunctionType;
    class Value;
    class Label;
    class IRContext;
    class Instruction;
    class InstructionStream;
    class BasicBlock;

    /// <summary>
    ///  这个描述了一个函数,包含了一堆指令
    /// </summary>
    class Function {
    public:
        explicit Function();
        explicit Function(const char* name, FunctionType const* funcType);
        explicit Function(char const* name, FunctionType const* funcType, std::shared_ptr<Scope> up );

        void addArgs(Value * value);
        std::string const& getFunctionName() const;
        std::shared_ptr<NameAlloc> getNameAlloc() const;
        Label* findLabel(std::string const& label) const;
        bool   insertLabel(std::string const& name, Label* label);
        void   insertValue( Value * value);
        std::shared_ptr<Scope> getFunctionScope() const;
        FunctionType const*    getFunctionType() const;
        size_t getArgsSize() const;
        Value* getArgsAt(size_t i) const;
        uint32_t verifyFunction();
        std::shared_ptr<FlowGraphs> getFlowGraphs();
        Instruction* begin();
        Instruction* end();
        Instruction const* begin() const;
        Instruction const* end() const;
        Instruction* first();
        Instruction const* first() const;
        Instruction* last();
        Instruction const* last() const;
    private:
        friend class IRContext;
        friend class TextIRWriteVisitor;
        void _InsertIns(Instruction* ins);
    private:
        std::string                    m_name;
        std::vector<Value*>            m_args;

        std::shared_ptr<Scope>         m_functionScope;
        std::shared_ptr<NameAlloc>     m_nameAlloc;
        std::shared_ptr<ConstantTable> m_constantTable;
        std::shared_ptr<LabelTable>    m_labelTable;
        FunctionType const*            m_type;
        ADT::plist<IR::Instruction>    m_instructions;
        std::shared_ptr<FlowGraphs>    m_controlFlowGraphs;
        std::vector<Variable*>         m_variableTable;
    };
}