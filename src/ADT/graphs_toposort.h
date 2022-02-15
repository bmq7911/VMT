#pragma once
#include "ADT/graphs.h"
#include <vector>
namespace ADT {

	template<template<typename ... _Args> class C, typename V, typename E, typename Key>
	std::vector<ADT::vertex<V>*> get_start_vertex(ADT::adjacency_list<C, V, E, Key>& G) {
		std::vector<ADT::vertex<V>*> startVertex;
		for (auto iter = G.vertexBegin(); iter != G.vertexEnd(); ++iter) {
			auto kter = G.preEdgeBegin( * iter);
			if (kter == G.preEdgeEnd(*iter)) {
				startVertex.push_back(*iter);
			}
		}
		return startVertex;
	}
	template<template<typename ... _Args> class C, typename V, typename E, typename Key>
	std::vector<ADT::vertex<V>*> get_end_vertex( ADT::adjacency_list<C,V,E,Key>&G) {
		std::vector<ADT::vertex<V>*> endVertex;
		for (auto iter = G.vertexBegin(); iter != G.vertexEnd(); ++iter) {
			auto kter = G.edgeBegin(*iter);
			if (kter == G.edgeEnd(*iter)) {
				endVertex.push_back(*iter);
			}
		}
		return endVertex;
	
	}

	
	template<template<typename ... _Args> class C, typename V, typename E = void, typename Key = void>
	class adjacency_list_topo_sort {
	public:
		adjacency_list_topo_sort(ADT::adjacency_list<C,V,E,Key> & G) 
			: m_G( G )
		{ }
		std::vector < std::vector<ADT::vertex<V>*>> operator()() {
			std::map<ADT::vertex<V>*, std::set<ADT::edge<ADT::vertex<V>, E>>> predecessor;
			std::map<ADT::vertex<V>*, std::set<ADT::vertex<V>*, ADT::edge<ADT::vertex<V>, E>> > successor;
		}
	private:
		ADT::adjacency_list<C, V, E, Key>& m_G;
		std::vector<std::vector<ADT::vertex<V>*>> m_topo_sort;
	};
	

}