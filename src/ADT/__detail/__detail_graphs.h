#pragma once
#include <stdint.h>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
namespace ADT{

namespace graph{

struct no_property{};

namespace __detail{

    template< typename V, typename E, bool direct>
    struct __graphs_list_base;

    template<typename V,typename E, bool direct>
    class __Vertex;

    template<typename T>
    using __Pair = std::pair<T,T>;


    template<typename V1, typename E1, bool direct1, typename ... _Args >
    __Pair<__Vertex<V1,E1,direct1>*> __Link( __Vertex<V1,E1,direct1> *src, __Vertex<V1,E1,direct1> *dst, _Args&& ... args);

    template<typename V1, bool direct1>
    __Pair<__Vertex<V1,ADT::graph::no_property,direct1>*> __Link( __Vertex<V1,ADT::graph::no_property,direct1> *src, __Vertex<V1,ADT::graph::no_property,direct1> *dst);


    template<typename V1, typename E1, bool direct1>
    __Pair<__Vertex<V1,E1,direct1>*> __DisLink( __Vertex<V1,E1,direct1> *src, __Vertex<V1,E1,direct1> *dst);

    template<typename V1,  bool direct1>
    __Pair<__Vertex<V1,ADT::graph::no_property,direct1>*> __DisLink( __Vertex<V1,ADT::graph::no_property,direct1> *src, __Vertex<V1,ADT::graph::no_property,direct1> *dst);

    template<typename V,typename E>
    class __iterator;

    template<typename V,typename E>
    class __const_iterator;


    template<typename Vertex, typename E>
    Vertex* __get_vertex( __iterator<Vertex,E> iter);

    template<typename Vertex, typename E>
    Vertex const * __get_vertex( __const_iterator<Vertex,E> iter);

    


    template<typename V, typename E>
    struct __graph_continer_trait{
        using type                = std::unordered_map<V*,E*>;
        using type_iterator       = typename std::unordered_map<V*,E*>::iterator;
        using type_const_iterator = typename std::unordered_map<V*,E*>::const_iterator;

        using value_type          = E;
        using pointer             = E*;
        using reference           = E&;
        using const_reference     = E const&;
        using const_pointer       = E const*;
        static reference __GetRef( type_iterator iter){
            return *(iter->second);
        }
        static pointer   __GetPtr( type_iterator iter){
            return iter->second;
        }
        static const_reference __GetRef( type_const_iterator iter){
            return *(iter->second);
        }
        static const_pointer   __GetPtr( type_const_iterator iter){
            return iter->second;
        }
        static V* __GetVertex( type_iterator iter){
            return iter->first;
        }
        static V const* __GetVertex(type_const_iterator iter) {
            return iter->first;
        }
    };
#ifdef _WIN32
    template< typename V>
    struct __graph_continer_trait<V,no_property>{
        using type                = std::unordered_set<V*>;
        using type_iterator       = typename std::unordered_set<V*>::iterator;
        using type_const_iterator = typename std::unordered_set<V*>::const_iterator;

        using value_type          = no_property;
        using pointer             = no_property*;
        using reference           = no_property&;
        using const_reference     = no_property const&;
        using const_pointer       = no_property const*;
        static reference __GetRef( type_iterator iter) = delete;
        static pointer   __GetPtr( type_iterator iter) = delete;
        //static const_reference __GetRef( type_const_iterator iter) = delete;
        //static const_pointer   __GetPtr( type_const_iterator iter) = delete;
        static V* __GetVertex( type_iterator iter){
            return *iter;
        }
        //static V const* __GetVertex(type_const_iterator iter) {
        //    return *iter;
        //}
    };
#else
    template< typename V>
    struct __graph_continer_trait<V,no_property>{
        using type                = std::unordered_set<V*>;
        using type_iterator       = typename std::unordered_set<V*>::iterator;
        using type_const_iterator = typename std::unordered_set<V*>::const_iterator;

        using value_type          = no_property;
        using pointer             = no_property*;
        using reference           = no_property&;
        using const_reference     = no_property const&;
        using const_pointer       = no_property const*;
        static reference __GetRef( type_iterator iter) = delete;
        static pointer   __GetPtr( type_iterator iter) = delete;
        static const_reference __GetRef( type_const_iterator iter) = delete;
        static const_pointer   __GetPtr( type_const_iterator iter) = delete;
        static V* __GetVertex( type_iterator iter){
            return *iter;
        }
        static V const* __GetVertex(type_const_iterator iter) {
            return *iter;
        }
    };

#endif/// _WIN32
    template<typename V,typename E>
    class __iterator : public __graph_continer_trait<V,E>::type_iterator{
        public:
            using super = typename __graph_continer_trait<V,E>::type_iterator;
            typedef typename super::difference_type difference_type;
            typedef typename super::iterator_category iterator_category;
            typedef V vertex;
            typedef E  value_type;
            typedef E* pointer;
            typedef E& reference;


            using __graph_continer_trait<V,E>::type_iterator::type_iterator;
            __iterator( typename __graph_continer_trait<V,E>::type_iterator i)
                : __graph_continer_trait<V,E>::type_iterator( i )
            {
            }

            reference operator*() const{
                return __graph_continer_trait<V,E>::__GetRef( *this );
            }
            pointer operator->() const{
                return __graph_continer_trait<V,E>::__GetPtr(*this);
            }
            vertex * get_vertex() {
                return __GetVertex();
            }
            vertex const* get_vertex() const {
                return 
            }
    private:
            vertex* __GetVertex(){
                return __graph_continer_trait<V,E>::__GetVertex(*this);
            }
            vertex const* __GetVertex()const {
                return __graph_continer_trait<V, E>::__GetVertex(*this);
            }
            template<typename V1,typename E1>
            friend V1* __get_vertex( __iterator<V1,E1> iter);

    };

    template<typename V>
    class __iterator<V,no_property> : public __graph_continer_trait<V,no_property>::type_iterator{
    public:
            using super = typename __graph_continer_trait<V,no_property>::type_iterator;
            typedef typename super::difference_type   difference_type;
            typedef typename super::iterator_category iterator_category;
            typedef V vertex;
            typedef no_property  value_type;
            typedef no_property* pointer;
            typedef no_property& reference;

            using __graph_continer_trait<V,no_property>::type_iterator::type_iterator;
            //__iterator( typename std::unordered_set<V*>::iterator i)
            __iterator( typename __graph_continer_trait<V,no_property>::type_iterator i)
                : __graph_continer_trait<V,no_property>::type_iterator( i)
            {
            }

            reference operator*() const = delete;
            pointer operator->() const = delete;
            vertex* get_vertex() {
                return __GetVertex();
            }
            vertex const* get_vertex() const {
                return __GetVertex();
            }
    private:
            V* __GetVertex(){
                return __graph_continer_trait<V,ADT::graph::no_property>::__GetVertex(*this);
            }
            V const* __GetVertex() const {
                return __graph_continer_trait<V,ADT::graph::no_property>::__GetVertex(*this);
            }
            template<typename V1,typename E1>
            friend V1* __get_vertex( __iterator<V1,E1> iter);
    };

    template<typename V,typename E>
    class __const_iterator  : public __graph_continer_trait<V,E>::type_const_iterator{
        public:
            using super = typename __graph_continer_trait<V,E>::type_const_iterator;
            typedef typename super::difference_type difference_type;
            typedef typename super::iterator_category iterator_category;
            typedef V vertex;
            typedef E value_type;
            typedef E const* pointer;
            typedef E const& reference;

            //using typename std::unordered_map<V*,E*>::const_iterator::_Node_const_iterator;
            using __graph_continer_trait<V,E>::type_const_iterator::type_const_iterator;
            //__const_iterator( typename std::unordered_map<V*,E*>::const_iterator i)
            __const_iterator( typename __graph_continer_trait<V,E>::type_const_iterator i)
                : __graph_continer_trait<V,E>::type_const_iterator( i )
            {
            }

            reference operator*() const{
                return __graph_continer_trait<V,E>::__GetRef( *this);
            }
            pointer operator->() const{
                return __graph_continer_trait<V,E>::__GetPtr( *this);
            }
    private:
            V const* __GetVertex(){
                return __graph_continer_trait<V,E>::__GetVertex(*this);
            }
            template<typename V1,typename E1>
            friend V1 const* __get_vertex( __const_iterator<V1,E1> iter);
    };

    template<typename V>
    class __const_iterator<V,no_property>  : public __graph_continer_trait<V,no_property>::type_const_iterator{
        public:
            using super = typename __graph_continer_trait<V,no_property>::type_const_iterator;
            typedef typename super::difference_type difference_type;
            typedef typename super::iterator_category iterator_category;
            typedef V vertex;
            typedef no_property value_type;
            typedef no_property const* pointer;
            typedef no_property const& reference;

            //using typename std::unordered_set<V*,no_property*>::const_iterator::_Node_const_iterator;
            using __graph_continer_trait<V,no_property>::type_const_iterator::type_const_iterator;
            //__const_iterator( typename std::unordered_set<V*,no_property*>::const_iterator i)
            __const_iterator( typename __graph_continer_trait<V*,no_property*>::type_const_iterator i)
                : __graph_continer_trait<V,no_property>::type_const_iterator( i)
            {
            }

            reference operator*() const = delete;
            pointer operator->() const = delete;
    private:
            V const* __GetVertex(){
                return __graph_continer_trait<V,ADT::graph::no_property>::__GetVertex(*this);
            }
            template<typename V1,typename E1>
            friend V1 const* __get_vertex( __iterator<V1,E1> iter);
    };

    ///
    
    
    template<typename Vertex, typename E>
    Vertex* __get_vertex( __iterator<Vertex,E> iter){
        return iter.__GetVertex();
    }
    template<typename Vertex, typename E>
    Vertex const* __get_vertex( __const_iterator<Vertex,E> iter){
        return iter.__GetVertex();
    }

    template<typename V, typename E>
    class __Vertex<V,E,true>{
    public:
        using vertex = __Vertex<V,E,true>;
        using vertex_property = typename std::remove_cv<V>::type;
        using edge_property   = typename std::remove_cv<E>::type;
        using succ_iterator        = __iterator<vertex, edge_property>;
        using succ_const_iterator  = __const_iterator<vertex, edge_property>;
        using pred_iterator        = typename std::unordered_set<__Vertex<V,E,true>*>::iterator;
        using pred_const_iterator  = typename std::unordered_set<__Vertex<V,E,true>*>::const_iterator;
        using edge_continer        = typename __graph_continer_trait<vertex,edge_property>::type;
        static const bool direct_property = true;
    public:
        //__Vertex(){  }
        template<typename ... _Args>
        __Vertex( _Args && ...args)
            : m_data( std::forward<_Args>(args)...)
        {}
 
        vertex_property& data() {
            return m_data;
        }
        vertex_property const& data() const {
            return m_data;
        }
        std::pair< succ_iterator, succ_iterator  > get_succ_iter() {
            return std::make_pair(m_edges.begin(), m_edges.end());
        }
        std::pair< succ_const_iterator, succ_iterator> get_succ_iter() const {
            return std::make_pair(m_edges.begin(), m_edges.end());
        }
        std::pair<pred_iterator, pred_iterator > get_pred_iter() {
            return std::make_pair( m_predecessor.begin(), m_predecessor.end());
        }
        std::pair<pred_const_iterator, pred_const_iterator> get_pred_iter() const {
            return std::make_pair(m_predecessor.begin(), m_predecessor.end());
        }
    private:

        template<typename V1, typename E1, typename ... _Args >
        friend __Pair<__Vertex<V1,E1,true>*> __Link( __Vertex<V1,E1,true> *src, __Vertex<V1,E1,true> *dst, _Args&& ... args);

        template<typename V1>
        friend __Pair<__Vertex<V1,ADT::graph::no_property,true>*> __Link( __Vertex<V1,ADT::graph::no_property,true> *src, __Vertex<V1,ADT::graph::no_property,true> *dst);

        template<typename V1, typename E1>
        friend __Pair<__Vertex<V1,E1,true>*> __DisLink( __Vertex<V1,E1,true> *src, __Vertex<V1,E1,true> *dst);

        template<typename V1>
        friend __Pair<__Vertex<V1,ADT::graph::no_property,true>*> __DisLink( __Vertex<V1,ADT::graph::no_property,true> *src, __Vertex<V1,ADT::graph::no_property,true> *dst);
    private:
        vertex_property                                             m_data;
        typename __graph_continer_trait<vertex,edge_property>::type m_edges;
        std::unordered_set<__Vertex<V,E,true>*>                     m_predecessor;
    };
 
    template<typename V, typename E>
    class __Vertex<V,E,false>{
    public:
        using vertex = __Vertex<V,E,false>;
        using vertex_property = typename std::remove_cv<V>::type;
        using edge_property   = typename std::remove_cv<E>::type;

        using succ_iterator        = __iterator<vertex, edge_property>;
        using succ_const_iterator  = __const_iterator<vertex, edge_property>;
        using pred_iterator        = __iterator<vertex, edge_property>;
        using pred_const_iterator  = __const_iterator<vertex, edge_property>;
        using edge_continer        = typename __graph_continer_trait<vertex,edge_property>::type;
        static const bool direct_property = false;
    public:
        //__Vertex(){}
        template<typename ... _Args>
        __Vertex( _Args && ...args)
            : m_data( std::forward<_Args>(args)...)
        {}
        vertex_property& data() {
            return m_data;
        }
        vertex_property const& data() const {
            return m_data;
        }
        std::pair< succ_iterator, succ_iterator  > get_succ_iter() {
            return std::make_pair(m_edges.begin(), m_edges.end());
        }
        std::pair< succ_const_iterator, succ_iterator> get_succ_iter() const {
            return std::make_pair(m_edges.begin(), m_edges.end());
        }
        std::pair<pred_iterator, pred_iterator > get_pred_iter() {
            return std::make_pair(m_edges.begin(),m_edges.end());
        }
        std::pair<pred_const_iterator, pred_const_iterator> get_pred_iter() const {
            return std::make_pair(m_edges.begin(),m_edges.end());
        }
    private:

        template<typename V1, typename E1, typename ... _Args >
        friend __Pair<__Vertex<V1,E1,false>*> __Link( __Vertex<V1,E1,false> *src, __Vertex<V1,E1,false> *dst, _Args&& ... args);

        template<typename V1>
        friend __Pair<__Vertex<V1,ADT::graph::no_property,false>*> __Link( __Vertex<V1,ADT::graph::no_property,false> *src, __Vertex<V1,ADT::graph::no_property,false> *dst);
        template<typename V1, typename E1>
        friend __Pair<__Vertex<V1,E1,false>*> __DisLink( __Vertex<V1,E1,false> *src, __Vertex<V1,E1,false> *dst);

        template<typename V1>
        friend __Pair<__Vertex<V1,ADT::graph::no_property,false>*> __DisLink( __Vertex<V1,ADT::graph::no_property,false> *src, __Vertex<V1,ADT::graph::no_property,false> *dst);
    private:
        vertex_property m_data;
        typename __graph_continer_trait<vertex,edge_property>::type m_edges;
    };

    template<typename Vertex, typename ... _Args>
    Vertex* __GenVertex(_Args && ... args){
        Vertex* ptr = std::allocator<Vertex>().allocate( 1 );
        if( nullptr != ptr){
            std::allocator<Vertex>().construct(ptr, std::forward<_Args>(args) ...);
        }
        return ptr;
    }

    template<typename Vertex>
    void __DestroyVertex( Vertex* ptr){
        if( nullptr != ptr ){
            std::allocator<Vertex>().destroy( ptr);
            std::allocator<Vertex>().deallocate( ptr,1);
        }
    }


    template<typename V1, typename E1, typename ... _Args >
    __Pair<__Vertex<V1,E1,true>*> __Link( __Vertex<V1,E1,true> *src, __Vertex<V1,E1,true> *dst, _Args&& ... args){
        if( nullptr == src || nullptr == dst){
            return __Pair<__Vertex<V1,E1,true>*>( nullptr, nullptr);
        }
        else{
            auto iter = src->m_edges.find( dst );
            if( iter != src->m_edges.end()){
                return __Pair<__Vertex<V1,E1,true>*>( nullptr, nullptr);
            }
            else{
                
                auto ptr_edge_property = std::allocator<typename __Vertex<V1,E1,true>::edge_property>().allocate(1);
                if( nullptr == ptr_edge_property ){
                    return __Pair<__Vertex<V1,E1,true>*>( nullptr, nullptr);
                }
                else{
                    //std::_Construct( ptr_edge_property,std::forward<_Args>(args)...);
                    std::allocator<typename __Vertex<V1, E1,true>::edge_property>().construct( ptr_edge_property, std::forward<_Args>(args)... );
                    src->m_edges.insert( std::make_pair(dst, ptr_edge_property) );
                    dst->m_predecessor.insert( src);
                    return __Pair<__Vertex<V1,E1,true>*>( src,dst);
                }
                
            }

        }
    }
    
    template<typename V1>
    __Pair<__Vertex<V1,ADT::graph::no_property,true>*> __Link( __Vertex<V1,ADT::graph::no_property,true> *src,
                                                               __Vertex<V1,ADT::graph::no_property,true> *dst){
        using vertex = __Vertex<V1,ADT::graph::no_property,true>;

        if( nullptr == src || nullptr == dst){
            return __Pair<vertex*>( nullptr, nullptr);
        }
        else{
            auto iter = src->m_edges.find( dst );
            if( iter != src->m_edges.end()){
                return __Pair<vertex*>( nullptr, nullptr);
            }
            else{
                src->m_edges.insert( dst );
                dst->m_predecessor.insert( src);
                return __Pair<vertex*>( src,dst);
            }

        }
    }
    
    
    template<typename V1, typename E1, typename ... _Args>
    __Pair<__Vertex<V1,E1,false>*> __Link( __Vertex<V1,E1,false> *src, __Vertex<V1,E1,false>* dst, _Args && ... args){
        if( nullptr == src || nullptr == dst)
            return __Pair<__Vertex<V1,E1,false>*>( nullptr, nullptr);
        auto iter = src->m_edges.find( dst);
        auto kter = dst->m_edges.find( src);
        if( iter != src->m_edges.end() || kter != dst->m_edges.end()){
            return __Pair<__Vertex<V1,E1,false>*>( nullptr, nullptr);
        }
        
        auto ptr_edge_property = std::allocator<typename __Vertex<V1,E1,false>::edge_property>().allocate(1);
        if( nullptr == ptr_edge_property)
            return __Pair<__Vertex<V1,E1,false>*>( nullptr, nullptr);


        std::allocator<typename __Vertex<V1, E1, false>::edge_property>().construct( ptr_edge_property, std::forward<_Args>(args)... );
        


        src->m_edges.insert(std::make_pair(dst, ptr_edge_property));
        dst->m_edges.insert(std::make_pair(src, ptr_edge_property ));
        return __Pair<__Vertex<V1,E1,false>*>( src, dst);

    }
    
    template<typename V1>
    __Pair<__Vertex<V1,ADT::graph::no_property,false>*> __Link( __Vertex<V1,ADT::graph::no_property,false> *src, 
                                                                __Vertex<V1,ADT::graph::no_property,false>* dst){
        using vertex = __Vertex<V1,ADT::graph::no_property,false>;
        if( nullptr == src || nullptr == dst)
            return __Pair<vertex*>( nullptr, nullptr);
        auto iter = src->m_edges.find( dst);
        auto kter = dst->m_edges.find( src);
        if( iter != src->m_edges.end() || kter != dst->m_edges.end()){
            return __Pair<vertex*>( nullptr, nullptr);
        }
        src->m_edges.insert(dst);
        dst->m_edges.insert(src);
        return __Pair<vertex*>( src, dst);

    }
    
    template<typename V1, typename E1>
    __Pair<__Vertex<V1,E1,true>*> __DisLink( __Vertex<V1,E1,true> *src, __Vertex<V1,E1,true> *dst){
        if( nullptr == src || nullptr == dst )
            return __Pair<__Vertex<V1,E1,true>*>( nullptr, nullptr);
        auto iter = src->m_edges.find( dst );
        if( iter == src->m_edges.end() )
            return __Pair<__Vertex<V1,E1,true>*>( src,dst);
        ///1 .remove the dst->m_predecessor's src
        auto kter = dst->m_predecessor.find( src);
        dst->m_predecessor.erase( kter );

        typename __Vertex<V1,E1,true>::edge_property * property = iter->second;
        std::allocator<typename __Vertex<V1,E1,true>::edge_property>().destroy( property);
        std::allocator<typename __Vertex<V1,E1,true>::edge_property>().deallocate( property, 1);
        src->m_edges.erase( iter );
        return __Pair<__Vertex< V1,E1,true>*>( src, dst);
    }

    template<typename V1>
    __Pair<__Vertex<V1,ADT::graph::no_property,true>*> __DisLink( __Vertex<V1,ADT::graph::no_property,true> *src, __Vertex<V1,ADT::graph::no_property,true> *dst){
        using vertex = __Vertex<V1,ADT::graph::no_property,true>;
        if( nullptr == src || nullptr == dst )
            return __Pair<vertex*>( nullptr, nullptr);
        auto iter = src->m_edges.find( dst );
        if( iter == src->m_edges.end() )
            return __Pair<vertex*>( src,dst);
        ///1 .remove the dst->m_predecessor's src
        auto kter = dst->m_predecessor.find( src);
        dst->m_predecessor.erase( kter );

        src->m_edges.erase( iter );
        return __Pair<vertex*>( src, dst);
    }

    template<typename V1, typename E1>
    __Pair<__Vertex<V1,E1,false>*> __DisLink( __Vertex<V1,E1,false> *src, __Vertex<V1,E1,false> * dst){
        using __vertex = __Vertex<V1,E1,false>;
        if( nullptr == src || nullptr == dst)
            return __Pair<__vertex*>( nullptr,nullptr);
        auto iter = src->m_edges.find( dst );
        typename __Vertex<V1,E1,false>::edge_property * property = iter->second;
        auto kter = dst->m_edgs.find(src);

        std::allocator<typename __Vertex<V1,E1,false>::edge_property>().destroy( property);
        std::allocator<typename __Vertex<V1,E1,false>::edge_property>().deallocate( property ,1);
        src->m_edges.erase( iter);
        dst->m_edges.erase( kter);
        return __Pair<__vertex*>( src, dst);
    }

    template<typename V1>
    __Pair<__Vertex<V1,ADT::graph::no_property,false>*> __DisLink( __Vertex<V1,ADT::graph::no_property,false> *src, __Vertex<V1,ADT::graph::no_property,false> * dst){
        using vertex = __Vertex<V1,ADT::graph::no_property,false>;
        if( nullptr == src || nullptr == dst)
            return __Pair<vertex*>( nullptr,nullptr);
        auto iter = src->m_edges.find( dst );
        auto kter = dst->m_edgs.find(src);

        src->m_edges.erase( iter);
        dst->m_edges.erase( kter);
        return __Pair<vertex*>( src, dst);
    }

}



}
}
