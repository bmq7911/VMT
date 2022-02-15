#pragma once
#include <string>
#include <vector>
#include "ADT/graphs.h"


namespace dot {
	template<template<typename ..._Args> class C, typename  V, typename E= void, typename Key = void>
	class adjacency_list_dot_codegen {
	public:
		adjacency_list_dot_codegen()
			: m_G( nullptr )
		{}
		adjacency_list_dot_codegen(ADT::adjacency_list<C, V, E, Key>* G) 
			: m_G( G )
		{}
		template<typename VGen, typename EGen>
		std::string codegen( std::string const& name ) {
			if (nullptr == m_G) {
				return std::string();
			}
			std::stringstream ss;
			return _Codegen_Graph<VGen,EGen>( ss ,name );
		}
	private:
		template<typename VGen, typename EGen>
		std::string _Codegen_Graph(  std::stringstream & ss ,std::string name) {
			ss << "strict digraph " << name << "{\r\n";
			auto iter = m_G->vertexBegin();
			uint32_t index = 0;
			std::map<ADT::vertex<V>*, uint32_t> maps;
			for (; iter != m_G->vertexEnd();++index, ++iter) {
				_Codegen_Vertex<VGen>(*iter,index, ss);
				maps.insert( std::make_pair( * iter, index ));
			}
			iter = m_G->vertexBegin();
			for (; iter != m_G->vertexEnd(); ++iter) {
				_Codegen_Edges<EGen>(*iter, maps, ss);
			}

			ss << "}\r\n";
			return ss.str();
		}
		template<typename VGen>
		void _Codegen_Vertex( ADT::vertex<V>* v, uint32_t index, std::stringstream& ss) {
			ss << "vertex_" << index <<"[";
			VGen vgen( v );
			vgen(ss);
			ss << "];\r\n";
		}
		template<typename EGen>
		void _Codegen_Edges(ADT::vertex<V>* v, std::map<ADT::vertex<V>*, uint32_t>& maps, std::stringstream& ss) {
			auto iter = maps.find(v);
			if (iter != maps.end()) {
				auto kter = m_G->edgeBegin(v);
				auto kend = m_G->edgeEnd(v);
				if (kter != kend) {
					for (; kter != kend; ++kter ) {
						ss << "vertex_" << iter->second << " -> ";
						auto dst = kter->dst();
						auto dstV = maps.find(dst);
						if (dstV != maps.end()) {
							ss << " vertex_" << dstV->second<<" [";
						}

						EGen egen( kter->src(), kter->dst());
						egen(ss);
						ss << "];\r\n";
					}
				}
			}
		}
	private:
		/// <summary>
		/// 由于这个已经有了图形结构,按道理我们使用递归下降就能正常实现代码
		/// </summary>
		ADT::adjacency_list<C, V, E, Key>* m_G;
	};

}