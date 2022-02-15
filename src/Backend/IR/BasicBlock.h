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
    };

}