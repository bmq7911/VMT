#include "Backend/IR/BasicBlock.h"
#include "Backend/IR/Function.h"

namespace IR {
    BasicBlock::BasicBlock( Function* func )
        : m_index( 0 )
        , m_bStart( false )
        , m_bEnd( false )
        , m_beginIns( nullptr)
        , m_endIns(nullptr)
        , m_firstIns( nullptr )
        , m_lastIns( nullptr )
        , m_func( func )
    {
    }




    
    Instruction* BasicBlock::begin() {
        return m_beginIns;
    }

    Instruction const* BasicBlock::begin() const {
        return m_beginIns;
    }

    Instruction* BasicBlock::end() {
        return m_endIns;
    }

    Instruction const* BasicBlock::end() const {
        return m_endIns;
    }

    Instruction* BasicBlock::first() {
        return m_firstIns;
    }

    Instruction const* BasicBlock::first() const {
        return m_firstIns;
    }

    Instruction* BasicBlock::last() {
        return m_lastIns;
    }

    Instruction const* BasicBlock::last() const {
        return m_lastIns;
    }

    void BasicBlock::_AnalysisValueType( ) {
            //1. 遍历所有的指令
            for (auto ins = m_beginIns; ins != m_endIns; ins = ins->getNext()) {
                /// 2. 遍历每条指令的操作数
                for (auto kter = ins->operandBegin(); kter != ins->operandEnd(); ++kter) {
                    Value* operand = *kter;
                    auto fiter = m_assignValue.find(operand);
                    /// 2.1 如果指令不在 内部定义之中,那么指令就是由外部引入
                    if (fiter == m_assignValue.end()) {
                        m_importValue.insert( operand );
                    }
                    m_allValues.insert(operand);
                }

                auto result_value = ins->getRetValue();
                auto fiter = m_assignValue.find( result_value );
                if (fiter != m_assignValue.end()) { /// 这里说明这个值在这个基本块内再次被赋值,那么这个指令就需要改写成 SSA
                    ///
                    m_needSSAChangedIns.insert(ins); /// 我们现在只是记录一下,等到后续来该写名称,原因是这个变量可能是导出变量
                }
                if (nullptr != result_value) {
                    m_assignValue.insert(result_value);
                }
                m_allValues.insert(result_value);
            }   
        }
    
    void BasicBlock::_AnalysisValueLive( ) {
            
    }




}