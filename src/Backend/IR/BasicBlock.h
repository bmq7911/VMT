#pragma once
#include <memory>
#include <vector>
#include <string>
#include <set>
#include "ADT/plist.h"
#include "Backend/IR/Value.h"


namespace IR {
    class FlowGraphs;
    class Function;
    class Instruction;

    class BasicBlock {
    public:
        BasicBlock(Function*);
        Instruction* begin();
        Instruction const* begin() const;
        Instruction* end();
        Instruction const* end() const;
        Instruction* first();
        Instruction const* first() const;
        Instruction* last();
        Instruction const* last() const;
        bool isStartBlock() const {
            return m_bStart;
        }
        bool isEndBlock() const {
            return m_bEnd;
        }
        uint32_t getIndex() const {
            return m_index;
        }

        std::set<Value*>& getImportValueSet() {
            return m_importValue;
        }
        std::set<Value*>& getAssignValueSet() {
            return m_assignValue;
        }
        /// <summary>
        ///  ����ͬʱҪ��д��SSA��ʽ
        /// </summary>
        void verifyBasicBlock() {
            _AnalysisValueType( );

        }
    private:
        void _AnalysisValueType();
        void _AnalysisValueLive( );
        /// 
    private:
        friend class FlowGraphs;
        uint32_t m_index;
        bool m_bStart;
        bool m_bEnd;
        Instruction* m_beginIns;
        Instruction* m_endIns;
        Instruction* m_firstIns;
        Instruction* m_lastIns;
        Function*    m_func;

        std::set<Value*> m_allValues;/// ���б���
        std::set<Value*> m_importValue;   /// ����ı���
        std::set<Value*> m_assignValue; /// �ڲ�����ı���
        std::set<Value*> m_outportValue;  /// �����ı���
        std::set<Instruction*> m_needSSAChangedIns; /// �����Ļ�Ծ�Է���

    };

}