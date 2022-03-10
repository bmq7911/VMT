#pragma once
#include <string>
#include <vector>
#include "ADT/graphs.h"


namespace dot {
	template< typename V, typename E = ADT::graph::no_property , bool direct = true >
	class adjacency_list_dot_codegen {
	public:
		using adjacency_list = ADT::graph::adjacency_list<V, E, direct>;
		adjacency_list_dot_codegen()
			: m_G( nullptr )
		{}
		adjacency_list_dot_codegen(adjacency_list * G) 
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
			auto iter = m_G->begin();

			uint32_t index = 0;
			std::map<ADT::graph::adjacency_list_trait<adjacency_list>::vertex, uint32_t> maps;
			for (; iter != m_G->end();++index, ++iter) {
				_Codegen_Vertex<VGen>(*iter,index, ss);
				maps.insert( std::make_pair( * iter, index ));
			}
			iter = m_G->begin();
			for (; iter != m_G->end(); ++iter) {
				_Codegen_Edges<EGen>(*iter, maps, ss);
			}

			ss << "}\r\n";
			return ss.str();
		}
		template<typename VGen>
		void _Codegen_Vertex( typename ADT::graph::adjacency_list_trait<adjacency_list>::vertex v,
						      uint32_t index, std::stringstream& ss) {
			ss << "vertex_" << index <<"[";
			VGen vgen( v );
			vgen(ss);
			ss << "];\r\n";
		}
		template<typename EGen>
		void _Codegen_Edges( typename ADT::graph::adjacency_list_trait<adjacency_list>::vertex v,
							 std::map<typename ADT::graph::adjacency_list_trait<adjacency_list>::vertex, uint32_t>& maps,
							 std::stringstream& ss) {
			auto iter = maps.find(v);
			if (iter != maps.end()) {
				//auto pred_pair = ADT::graph::get_vertex_pred_iter(v);
				auto succ_pair = v->get_succ_iter( );
				if (succ_pair.first != succ_pair.second ) {
					/// <summary>
					/// 这里获取的是 边的属性
					/// </summary>
					for (auto kter = succ_pair.first; kter != succ_pair.second; ++kter ) {
						auto dst = kter.get_vertex();

						ss << "vertex_" << iter->second << " -> ";
						auto dstV = maps.find(dst);
						if (dstV != maps.end()) {
							ss << " vertex_" << dstV->second<<" [";
						}

						EGen egen( v, dst );
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
		adjacency_list * m_G;
	};


	void dot_display( std::string const& dotstring ) {
		
	}
}