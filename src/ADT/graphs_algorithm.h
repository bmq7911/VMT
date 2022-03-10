#pragma once
#include "graphs.h"
#include <vector>
namespace ADT {
	namespace graph {
		/*
		namespace __detail {
			template<typename iter>
			struct __graph_iter_trait {
				using V = typename iter::vertex::vertex_property;
				using E = typename iter::vertex::edge_property;
				static const bool D = iter::vertex::direct_property;
			};
		}

		template<typename V,typename E, bool direct>
		edge_wrapper<V,E,direct> get_edge_wrapper<
			typename __detail::__graph_iter_trait<typename __detail::__Vertex<V,E,direct>::succ_iterator>::V,
			typename __detail::__graph_iter_trait<typename __detail::__Vertex<V,E,direct>::succ_iterator>::E,
		>( typename __detail::__Vertex<V,E,direct>::succ_iterator i) {
			
		}
		template<typename V, typename E, bool direct>
		const edge_wrapper<V,E,direct> get_edge_wrapper(typename __detail::__Vertex<V,E,direct>::succ_const_iterator i) {
		}
		


		template<typename V,typename E, bool direct>
		edge_wrapper<V,E,direct> get_edge_wrapper( typename __detail::__Vertex<V,E,direct>::pred_iterator i) {
		}
		template<typename V, typename E, bool direct>
		const edge_wrapper<V,E,direct> get_edge_wrapper(typename __detail::__Vertex<V,E,direct>::pred_const_iterator i) {
		}
		*/

		template<typename Vertex,typename Iter>
		auto get_vertex(Iter iter)->Vertex* {
			return __detail::__get_vertex( iter );
		}


		
		template<typename V, typename E>
		std::vector<typename ADT::graph::adjacency_list_trait<ADT::graph::adjacency_list<V,E,true>>::vertex > 
		get_start_vertex( ADT::graph::adjacency_list<V,E,true> & G ) {
			using GT = ADT::graph::adjacency_list<V, E, true>;
			std::vector<typename ADT::graph::adjacency_list_trait<GT>::vertex> startVertex;
			for (auto iter = G.begin(); iter != G.end(); ++iter) {
				auto pred_pair = (*iter)->get_pred_iter( );
				if (pred_pair.first == pred_pair.second) {
					startVertex.push_back(*iter);
				}
			}
			return startVertex;
		}
		template<typename V, typename E>
		std::vector<typename ADT::graph::adjacency_list_trait<ADT::graph::adjacency_list<V,E,true>>::const_vertex > 
		get_start_vertex( ADT::graph::adjacency_list<V,E,true> const & G ) {
			using GT = ADT::graph::adjacency_list<V, E, true>;
			std::vector<typename ADT::graph::adjacency_list_trait<GT>::const_vertex> startVertex;
			for (auto iter = G.begin(); iter != G.end(); ++iter) {
				auto pred_pair = (* iter)->get_pred_iter();
				if (pred_pair.first == pred_pair.second) {
					startVertex.push_back(*iter);
				}
			}
			return startVertex;
		}
		
		template<typename V, typename E>
		std::vector<typename ADT::graph::adjacency_list_trait<ADT::graph::adjacency_list<V,E,true>>::vertex> 
		get_end_vertex(ADT::graph::adjacency_list<V,E,true> & G) {
			using GT = ADT::graph::adjacency_list<V, E, true>;

			std::vector< typename ADT::graph::adjacency_list_trait<GT>::vertex > endVertex;
			for (auto iter = G.begin(); iter != G.end(); ++iter) {
				auto succ_pair = (*iter)->get_succ_iter();
				if ( succ_pair.first == succ_pair.second ) {
					endVertex.push_back(*iter);
				}
			}
			return endVertex;
		}
		template<typename V, typename E>
		std::vector<typename ADT::graph::adjacency_list_trait<ADT::graph::adjacency_list<V,E,true>>::const_vertex> 
		get_end_vertex(ADT::graph::adjacency_list<V,E,true> const & G) {
			using GT = ADT::graph::adjacency_list<V, E, true>;

			std::vector< typename ADT::graph::adjacency_list_trait<GT>::const_vertex > endVertex;
			for (auto iter = G.begin(); iter != G.end(); ++iter) {
				auto succ_pair = (*iter)->get_succ_pair();
				if ( succ_pair.first == succ_pair.second ) {
					endVertex.push_back(*iter);
				}
			}
			return endVertex;
		}



		template<typename G>
		class adjacency_list_topo_sort;

		template<typename V, typename E>
		class adjacency_list_topo_sort<ADT::graph::adjacency_list<V,E,true>> {
		public:
			using GT = ADT::graph::adjacency_list<V, E, true>;
			adjacency_list_topo_sort(ADT::graph::adjacency_list<V,E,true>& G)
				: m_G(G)
			{ }

		private:
			ADT::graph::adjacency_list<V,E,true>& m_G;
		};
	}

}
