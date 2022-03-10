#pragma once
#include <sstream>
#include "ADT/graphs.h"
#include "Backend/IR/BasicBlock.h"

namespace IR {

	class VertexBasicBlockDotCodeGen {
	public:
		using G = ADT::graph::adjacency_list<IR::BasicBlock>;
		VertexBasicBlockDotCodeGen(ADT::graph::adjacency_list_trait<G>::vertex BB) 
			: m_basicBlock( BB )
		{}

		void operator()(std::stringstream& ss) const {
			if (m_basicBlock->data().isStartBlock()) {
				ss << "shape=ellipse,label=\"Start\"";
			}
			else if ( m_basicBlock->data().isEndBlock() ) {
				ss << "shape=box,label=\"End\"";
			}
			else { 
				ss << "shape=box,label=\"BasicBlock_" << m_basicBlock->data().getIndex() << "\"";
			}
		}
	private:
		ADT::graph::adjacency_list_trait<G>::vertex m_basicBlock;
	
	};
	class EdgeBasicBlockDotCodeGen {
	public:
		using G = ADT::graph::adjacency_list<IR::BasicBlock>;
		EdgeBasicBlockDotCodeGen( ADT::graph::adjacency_list_trait<G>::vertex BS,
								  ADT::graph::adjacency_list_trait<G>::vertex BE  ) 
			: m_BS(BS)
			, m_BE(BE)
		{
		
		}
		void operator()(std::stringstream& ss) const {
			ss << "color=black";
		}
	private:
		ADT::graph::adjacency_list_trait<G>::vertex m_BS;
		ADT::graph::adjacency_list_trait<G>::vertex m_BE;

	};

}