#pragma once
#include <vector>
#include <memory>
#include <map>

#include "Backend/IR/IR.h"
#include "Backend/IR/BasicBlock.h"
#include "Backend/IR/Function.h"
#include "ADT/graphs.h"

namespace IR {
    class Instruction;
    
    /// <summary>
    ///  这个算法可以在基本指令建立后在来实现,我需要一个图的数据结构
    /// </summary>
    class FlowGraphs {
    public:
        class LoopPath {
            BasicBlock* m_entryBaiscBlock;
            std::vector<BasicBlock*> m_loopBasicBlock;
        };

    public:
        static std::shared_ptr<FlowGraphs> makeFlowGraphs( Function* function );
        
        size_t size() const {
            return m_flowGraph.vertexSize();
        }
        ADT::vertex<BasicBlock>* begin() {
            return m_beginBasicBlock;
        }
        ADT::vertex<BasicBlock>* end() {
            return m_endBasicBlock;
        }
        ADT::vertex<BasicBlock>const* begin() const {
            return m_beginBasicBlock;
        }
        ADT::vertex<BasicBlock> const* end() const {
            return m_endBasicBlock;
        }
        ADT::adjacency_list<std::set, IR::BasicBlock>& graphData() {
            return m_flowGraph;
        }
        ADT::adjacency_list<std::set, IR::BasicBlock> const& graphData() const {
            return m_flowGraph;
        }
    private:
        static std::vector<LoopPath> _InitLoop(std::vector<BasicBlock*> const& blocks);
            
        
    private:
        ADT::vertex<BasicBlock>* m_beginBasicBlock;
        ADT::vertex<BasicBlock>* m_endBasicBlock;
        ADT::adjacency_list<std::set,IR::BasicBlock> m_flowGraph;
    };


}