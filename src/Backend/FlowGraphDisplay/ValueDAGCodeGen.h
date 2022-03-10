#pragma once
#include <sstream>
#include "ADT/graphs.h"
#include "Backend/IR/ValueDAG.h"

namespace IR {
	
	class VertexValueDAGDotCodeGen {
	public:
		using G = ADT::graph::adjacency_list<IR::ValueDAG::Node>;
		VertexValueDAGDotCodeGen(typename ADT::graph::adjacency_list_trait<G>::vertex node) 
			: m_node( node )
		{}
		void operator()( std::stringstream& ss ) const {
			ss << "shape=circle,label=\"" << m_node->data().getValue()->getValueName() << "\"";
		}
	private:
		typename ADT::graph::adjacency_list_trait<G>::vertex m_node;
	};
	class EdgeValueDAGDotCodeGen {
	public:
		using G = ADT::graph::adjacency_list<IR::ValueDAG::Node>;
		EdgeValueDAGDotCodeGen(typename ADT::graph::adjacency_list_trait<G>::vertex s,
			                   typename ADT::graph::adjacency_list_trait<G>::vertex e) 
			: m_s( s )
			, m_e( e )
		{}
		void operator()(std::stringstream& ss) const {
			ss << "color=black";
		}
	private:
		typename ADT::graph::adjacency_list_trait<G>::vertex m_s;
		typename ADT::graph::adjacency_list_trait<G>::vertex m_e;
	};

}