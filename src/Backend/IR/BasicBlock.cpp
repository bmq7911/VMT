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
            //1. �������е�ָ��
            for (auto ins = m_beginIns; ins != m_endIns; ins = ins->getNext()) {
                /// 2. ����ÿ��ָ��Ĳ�����
                for (auto kter = ins->operandBegin(); kter != ins->operandEnd(); ++kter) {
                    Value* operand = *kter;
                    auto fiter = m_assignValue.find(operand);
                    /// 2.1 ���ָ��� �ڲ�����֮��,��ôָ��������ⲿ����
                    if (fiter == m_assignValue.end()) {
                        m_importValue.insert( operand );
                    }
                    m_allValues.insert(operand);
                }

                auto result_value = ins->getRetValue();
                auto fiter = m_assignValue.find( result_value );
                if (fiter != m_assignValue.end()) { /// ����˵�����ֵ��������������ٴα���ֵ,��ô���ָ�����Ҫ��д�� SSA
                    ///
                    m_needSSAChangedIns.insert(ins); /// ��������ֻ�Ǽ�¼һ��,�ȵ���������д����,ԭ����������������ǵ�������
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