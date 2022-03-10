#pragma once
#include <stdint.h>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include "__detail/__detail_graphs.h"

namespace ADT{

namespace graph{
    // 有向图
    template< typename V,typename E = ADT::graph::no_property, bool direct = true>
    struct adjacency_list{
    public:
        using iterator       = typename std::unordered_set<__detail::__Vertex<V,E,direct>* >::iterator;
        using const_iterator = typename std::unordered_set<__detail::__Vertex<V,E,direct>* >::const_iterator;

        using vertex_property = typename __detail::__Vertex<V,E,direct>::vertex_property;
        using edge_property   = typename __detail::__Vertex<V,E,direct>::edge_property;
        using vertex          = __detail::__Vertex<V,E,direct>*;
        using const_vertex    = __detail::__Vertex<V,E,direct> const*;

        adjacency_list(){
        }

        ~adjacency_list(){
            __DestroyGraph();
        }
        ///1. 图的拷贝很复杂
        adjacency_list( adjacency_list const& g ){
            _CopyGraph(g);
        }

        adjacency_list( adjacency_list && g )
            : m_vertex( std::move(g.m_vertex))
        {

        }

        adjacency_list& operator=( adjacency_list const& g){
            if( this != &g){
                _CopyGraph(g);
            }
            return *this;
        }

        adjacency_list& operator=( adjacency_list && g){
            if( this != &g){
                m_vertex = std::move( g.m_vertex );
            }
            return *this;
        }
        
        size_t size( ) const{
            return m_vertex.size( );
        }

        iterator begin() {
            return m_vertex.begin();
        }
        
        iterator end() {
            return m_vertex.end();
        }
        const_iterator begin() const{
            return m_vertex.begin();
        }
        const_iterator end() const{
            return m_vertex.end();
        }

        template<typename ... _Args>
        vertex add_vertex( _Args &&...  args){
            auto pVertex = __detail::__GenVertex<__detail::__Vertex<V,E,direct>>( std::forward<_Args>(args)...);
            if( nullptr != pVertex){
                m_vertex.insert( pVertex);
            }
            return pVertex;
        }

        template<typename ... _Args>
        std::pair<vertex,vertex> add_edge( vertex src, vertex dst, _Args && ... args) {
            if (nullptr == src || nullptr == dst) {
                return std::make_pair<vertex,vertex>(nullptr, nullptr);
            }
            if (!_IsHaveVertex(src) || !_IsHaveVertex(dst)) {
                return std::make_pair<vertex,vertex>(nullptr, nullptr);
            }
            else {
                return __detail::__Link(src, dst, std::forward<_Args>(args) ...);
            }
        }
    private:
        bool _IsHaveVertex(vertex v) const{
            auto iter = m_vertex.find(v);
            return iter != m_vertex.end() ? true : false;
        }
        void __DestroyGraph(){
            for( auto iter = m_vertex.begin(); iter != m_vertex.end(); ++iter){
                __detail::__Vertex<V,E,direct> * pVertex = *iter;
                if( nullptr != pVertex){
                    auto succ_pair = pVertex->get_succ_iter( );
                    while( succ_pair.first != succ_pair.second ) {
                        auto dst = __detail::__get_vertex( succ_pair.first );
                        __detail::__DisLink(pVertex, dst);
                        succ_pair = pVertex->get_succ_iter();
                    }
                }
            }
            for( auto iter = m_vertex.begin(); iter != m_vertex.end(); ++iter){
                __detail::__DestroyVertex( *iter);
            }
        }
        void _CopyGraph( adjacency_list const& g ) {
            std::unordered_map< __detail::__Vertex<V, E, direct>*, __detail::__Vertex<V, E, direct>* > origin_new_map;
            for (auto iter = g.begin(); iter != g.end(); ++iter) {
                auto origin_vertex = *iter;
                if (nullptr != origin_vertex) {
                    __detail::__Vertex<V, E, direct>* new_vertex = std::allocator<__detail::__Vertex<V, E, direct>>().allocate(1);
                    std::allocator<__detail::__Vertex<V, E, direct>>().construct( new_vertex, origin_vertex->data() );
                    origin_new_map.insert(std::make_pair( origin_vertex, new_vertex));
                }
            }
            for (auto iter = g.begin(); iter != g.end(); ++iter) {
                auto origin_vertex = *iter;
                auto src_vertex = origin_new_map.find(origin_vertex);

                if (nullptr != origin_vertex) {
                    auto succ_pair = origin_vertex->get_succ_iter();
                    for (auto kter = succ_pair.first; kter != succ_pair.second; ++kter) {
                        auto origin_dst = __detail::__get_vertex(kter);
                        auto dst_vertex = origin_new_map.find(origin_dst);
                        __Link(src_vertex->second, dst_vertex->second, kter, typename std::conditional<std::is_same<E, ADT::graph::no_property>::value, int, bool>::type{});
                    }
                }
            }
            for (auto iter = origin_new_map.begin(); iter != origin_new_map.end(); ++iter) {
                m_vertex.insert(iter->second);
            }
        }
        void __Link(  __detail::__Vertex<V,E,direct> * src,__detail::__Vertex<V,E,direct> *dst,
                      typename __detail::__Vertex<V,E,direct>::succ_iterator & iter ,bool  ) {
            __detail::__Link(src, dst, *iter);
        }
        void __Link(__detail::__Vertex<V, E, direct>* src, __detail::__Vertex<V, E, direct>* dst,
            typename __detail::__Vertex<V, E, direct>::succ_iterator& iter, int) {
            __detail::__Link(src, dst);
        }
    private:
        std::unordered_set<__detail::__Vertex<V,E,direct>* > m_vertex;
    };



    template<typename al>
    struct adjacency_list_trait;

    template<typename V, typename E, bool direct>
    struct adjacency_list_trait<adjacency_list<V, E, direct> > {
        using vertex_iterator       = typename adjacency_list<V, E, direct>::iterator;
        using vertex_const_iterator = typename adjacency_list<V, E, direct>::const_iterator;
        using vertex_property       = typename __detail::__Vertex<V, E, direct>::vertex_property;
        using edge_property         = typename __detail::__Vertex<V, E, direct>::edge_property;
        using vertex                = typename __detail::__Vertex<V, E, direct>*;
        using const_vertex          = typename __detail::__Vertex<V, E, direct> const*;
        using succ_iterator         = typename __detail::__Vertex<V, E, direct>::succ_iterator;
        using succ_const_iterator   = typename __detail::__Vertex<V, E, direct>::succ_const_iterator;
        using pred_iterator         = typename __detail::__Vertex<V, E, direct>::pred_iterator;
        using pred_const_iterator   = typename __detail::__Vertex<V, E, direct>::pred_const_iterator;
        const static bool value_direct    = direct;
    };

		template<typename V, typename E, bool direct>
		struct edge_wrapper;
		template<typename V, typename E>
		struct edge_wrapper<V,E,true> {
			__detail::__Vertex<V, E, true>* src;
			__detail::__Vertex<V, E, true>* dst;
			typename __detail::__Vertex<V, E, true>::edge_property* m_edgeData;
		};
		template<typename V, typename E>
		struct edge_wrapper<V, E, false> {
			__detail::__Vertex<V, E, true>* src;
			__detail::__Vertex<V, E, true>* dst;
		};



    template<typename V, typename E = ADT::graph::no_property, bool direct = true>
    using vertex = __detail::__Vertex<V, E, direct> *;
    template<typename V, typename E= ADT::graph::no_property, bool direct = true>
    using const_vertex = __detail::__Vertex<V, E, direct> const*;

}
}
