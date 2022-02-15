#pragma once
#include <sstream>
#include "ADT/graphs.h"
#include "Backend/IR/ValueDAG.h"

namespace IR {
	
	class VertexValueDAGDotCodeGen {
	public:
		VertexValueDAGDotCodeGen(ADT::vertex<IR::ValueDAG::Node>* node) 
			: m_node( node )
		{}
		void operator()( std::stringstream& ss ) const {
			ss << "shape=circle,label=\"" << m_node->data().getValue()->getValueName() << "\"";
		}
	private:
		ADT::vertex<IR::ValueDAG::Node>* m_node;
	};
	class EdgeValueDAGDotCodeGen {
	public:
		EdgeValueDAGDotCodeGen(ADT::vertex<IR::ValueDAG::Node>* s, ADT::vertex<IR::ValueDAG::Node>* e) 
			: m_s( s )
			, m_e( e )
		{}
		void operator()(std::stringstream& ss) const {
			ss << "color=black";
		}
	private:
		ADT::vertex<IR::ValueDAG::Node>* m_s;
		ADT::vertex<IR::ValueDAG::Node>* m_e;
	};

}