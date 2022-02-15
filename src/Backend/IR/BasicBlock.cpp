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

}