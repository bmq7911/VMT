#pragma once
#include <sstream>
#include "ADT/graphs.h"
#include "Backend/IR/BasicBlock.h"

namespace IR {

	class VertexBasicBlockDotCodeGen {
	public:
		VertexBasicBlockDotCodeGen(ADT::vertex<IR::BasicBlock>* BB) 
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
		ADT::vertex<IR::BasicBlock>* m_basicBlock;
	
	};
	class EdgeBasicBlockDotCodeGen {
	public:
		EdgeBasicBlockDotCodeGen( ADT::vertex<IR::BasicBlock>*BS, ADT::vertex<IR::BasicBlock>*BE  ) 
			: m_BS(BS)
			, m_BE(BE)
		{
		
		}
		void operator()(std::stringstream& ss) const {
			ss << "color=black";
		}
	private:
		ADT::vertex<IR::BasicBlock>* m_BS;
		ADT::vertex<IR::BasicBlock>* m_BE;

	};

}