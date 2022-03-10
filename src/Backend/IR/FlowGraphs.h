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
            return m_flowGraph.size();
        }
        ADT::graph::adjacency_list<IR::BasicBlock>::iterator begin() {
            return m_flowGraph.begin( );
        }
        ADT::graph::adjacency_list<IR::BasicBlock>::iterator end() {
            return m_flowGraph.end( );
        }
        ADT::graph::adjacency_list<IR::BasicBlock>::const_iterator begin() const {
            return m_flowGraph.begin( );
        }
        ADT::graph::adjacency_list<IR::BasicBlock>::const_iterator end() const {
            return m_flowGraph.end( );
        }
        ADT::graph::adjacency_list<IR::BasicBlock>& graphData() {
            return m_flowGraph;
        }
        ADT::graph::adjacency_list<IR::BasicBlock> const& graphData() const {
            return m_flowGraph;
        }
    private:
        static std::vector<LoopPath> _InitLoop(std::vector<BasicBlock*> const& blocks);
            
        
    private:
        ADT::graph::adjacency_list<IR::BasicBlock>::vertex m_beginBasicBlock;
        ADT::graph::adjacency_list<IR::BasicBlock>::vertex m_endBasicBlock;
        ADT::graph::adjacency_list<IR::BasicBlock> m_flowGraph;

    };


}