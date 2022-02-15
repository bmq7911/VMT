#pragma once
#include <stdint.h>
#include <list>
#include <set>
#include <map>

/// <summary>
///  图再整个编译器后端优化过程起到了很重要的作用,因此图一定要写好
/// </summary>
namespace ADT{


template<typename Vertex, typename ... _Args>
class edge;

template<typename T>
struct __d_link {
    __d_link() 
        : m_pre( nullptr )
        , m_next( nullptr )
    {}
    __d_link(__d_link const& link)
        : m_pre( link.m_pre)
        , m_next( link.m_next )
    {
    }
    __d_link& operator=(__d_link const& link) {
        if (this != &link) {
            m_pre = link.m_pre;
            m_next = link.m_next;
        }
        return *this;
    }
    T* getPre() const {
        return m_pre;
    }
    T* getNext() const {
        return m_next;
    }

    T* m_pre;
    T* m_next;

};

template<typename Vertex, typename ... _Args>
struct edge_base;

template<typename Vertex, typename T>
struct edge_base<Vertex,T>  :public __d_link<edge<Vertex,T>>{
    edge_base()
        : m_data()
    {}
    template<typename ... _Args>
    edge_base(_Args && ... args)
        : m_data( std::forward<_Args>(args) ... )
    {
    
    }
    T& data() {
        return m_data;
    }
    T const & data() const {
        return m_data;
    }
protected:
    T m_data;
};

template<typename Vertex>
struct edge_base<Vertex> : public __d_link<edge<Vertex>>  {
    edge_base() {}
};


template<typename Vertex , typename ... _Next>
class edge : public edge_base<Vertex,_Next...>{
    static_assert( sizeof...(_Next) ==0 || sizeof...(_Next) ==1 , "sizeof...(_Next) must 0 or 1");
public:
    edge()
        : edge_base<Vertex,_Next...>( )
        , m_src( nullptr)
        , m_dst( nullptr )
    {
    }

    template<typename ... _Args>
    edge( Vertex*v1, Vertex* v2,_Args && ...args)
        : edge_base<Vertex,_Next...>( std::forward<_Args>(args)...)
        , m_src( v1)
        , m_dst( v2)
    {
    }

    Vertex * src() {
        return m_src;
    }
    Vertex const* src() const{
        return m_src;
    }
    Vertex * dst() {
        return m_dst;
    }
    Vertex const* dst() const{
        return m_dst;
    }

private:
    template<typename ... _Args>
    edge* _Insert(edge* end, Vertex* src, Vertex* dst, _Args && ... args) {
        edge* newEdge = new edge(std::forward<_Args>(args) ...);
        if (nullptr == newEdge)
            return nullptr;
        return _InitNewEdge(end, src, dst, newEdge);
    }

    edge* _InitNewEdge(edge* end, Vertex* src, Vertex* dst, edge*newEdge) {
        newEdge->m_src = src;
        newEdge->m_dst = dst;

        edge* pre = end->m_pre;
        pre->m_next = newEdge;
        newEdge->m_pre = pre;
        newEdge->m_next = end;
        end->m_pre = newEdge;
        return newEdge;
    }

private:
    Vertex*    m_src;
    Vertex*    m_dst;
};


template<typename T>
class vertex{
public:
    vertex()
        : m_data()
    {
    }


    template<typename ... _Args>
    vertex( _Args && ... args)
        : m_data( std::forward<_Args>(args) ... )
    {
    }

    vertex( T && data)
        : m_data( data)
    {
    }

    T& data() {
        return m_data;
    }

    T const& data() const{
        return m_data;
    }

private:
    T m_data;
};


template<typename Vertex, typename C>
class __adjacency_list_base_set{
public:
    using iterator = typename C::iterator;
    using const_iterator = typename C::const_iterator;

    template<typename ... _Args>
    Vertex * add_vertex( _Args  &&... args){
        Vertex * ptrVertex = new Vertex( std::forward<_Args>(args) ... );
        if( nullptr != ptrVertex )
            m_container.insert( ptrVertex );
        return ptrVertex;
    }
    C & get_container() {
        return m_container;
    }
    C const& get_container() const{
        return m_container;
    }
protected:
    C m_container;
};

template<typename Key, typename Vertex, typename C>
class __adjacency_list_base_map{
public:
    using iterator = typename C::iterator;
    using const_iterator = typename C::const_iterator;

    template<typename ... _Args>
    Vertex add_vertex( Key key, _Args && ... args ){
        Vertex * ptrVertex = new Vertex( std::forward<_Args>(args) ... );
        if ( nullptr != ptrVertex ){
            m_container.insert( std::make_pair( key, ptrVertex ) );
        }
        return ptrVertex;
    }

    C & get_container() {
        return m_container;
    }

    C const& get_container() const{
        return m_container;
    }
protected:
    C m_container;
};



template<typename T, typename Ed,typename Key, template<typename ..._Args> class C >
struct __adjacency_list_container_trait{};

template< typename T, typename Ed,typename Key  >
struct __adjacency_list_container_trait<T,Ed,Key,std::set >{
    using type = __adjacency_list_base_set<vertex<T>,std::set<vertex<T>*>>;
};

template<typename T, typename Ed,typename Key>
struct __adjacency_list_container_trait<T,Ed,Key,std::multiset>{
    using type = __adjacency_list_base_set<vertex<T>,std::multiset<vertex<T>*>>;
};
template<typename T, typename Ed,typename Key>
struct __adjacency_list_container_trait<T,Ed,Key,std::map>{
    using type = __adjacency_list_base_map<Key,vertex<T>,std::map<Key,vertex<T>*>>;
};
template<typename T, typename Ed,typename Key>
struct __adjacency_list_container_trait<T,Ed,Key,std::multimap>{
    using type = __adjacency_list_base_map<Key,vertex<T>,std::multimap<Key,vertex<T>*>>;
};


/// <summary>
///  目前看来这个图的结构还不合理
/// </summary>
/// <typeparam name="Key"></typeparam>
/// <typeparam name="T"></typeparam>
/// <typeparam name="C"></typeparam>
template<template<typename ..._Args> class C, typename V, typename E = void, typename Key = void >
class adjacency_list : public __adjacency_list_container_trait<V, E,Key, C>::type {
public:
    using vertexIterator       = typename  __adjacency_list_container_trait<V,E,Key,C>::type::iterator;
    using const_vertexIterator = typename __adjacency_list_container_trait<V,E,Key,C>::type::const_iterator;
    using super          = typename __adjacency_list_container_trait<V,E,Key,C>::type;
    using Vertex         = vertex<V>;
    using Edge           = typename std::conditional<std::is_void<E>::value,edge<Vertex>,edge<Vertex,E>>::type;
public:
    template<typename T,bool bConst = false >
    class __edgeIterator : public std::iterator<std::bidirectional_iterator_tag, typename std::remove_cv<T>::type, ptrdiff_t,
                                               typename std::conditional<bConst, typename std::add_const<T>::type, T>::type *,
                                               typename std::conditional<bConst, typename std::add_const<T>::type, T>::type & > {
    public:
        using Self = __edgeIterator;
        using Base = std::iterator<std::bidirectional_iterator_tag, typename std::remove_cv<T>::type, ptrdiff_t,
                                   typename std::conditional<bConst, typename std::add_const<T>::type,T>::type* ,
                                   typename std::conditional<bConst, typename std::add_const<T>::type,T>::type &>;
        __edgeIterator()
            : m_ptr(nullptr)
        {}
        __edgeIterator( __edgeIterator const& i)
            : m_ptr( i.m_ptr )
        {
        }
        __edgeIterator(__d_link<typename std::remove_cv<T>::type >* ptr)
            : m_ptr( ptr )
        {
        }
        __edgeIterator& operator=( __edgeIterator const& i){
            if(this != &i ){
                m_ptr = i.m_ptr;
            }
            return *this;
        }
        bool operator==(const Self& x) const {
            return m_ptr == x.m_ptr;
        }
        bool operator != (const Self& x) const {
            return m_ptr != x.m_ptr;
        }
        typename Base::reference operator* () const {
            typename Base::pointer ptr = static_cast<typename Base::pointer>(m_ptr);
            return *ptr;
        }
        typename Base::pointer operator->() const {
            typename Base::pointer ptr = static_cast<typename Base::pointer>(m_ptr);
            return ptr;
        }
        Self& operator++() {
            m_ptr = m_ptr->getNext( );
            return *this;
        }
        Self operator++(int) {
            Self tmp = *this;
            ++(*this);
            return tmp;
        }
        Self& operator--() {
            m_ptr = m_ptr->getPre();
            return *this;
        }
        Self operator--(int) {
            Self tmp = *this;
            --(*this);
            return tmp;
        }
    private:
        typename std::conditional<bConst, __d_link<Edge>const *, __d_link<Edge>*>::type m_ptr;
    };

    using edgeIterator = __edgeIterator<Edge>;
    /*
    template<typename T>
    class __const_edgeIterator : public std::iterator<std::bidirectional_iterator_tag, typename std::remove_cv<T>::type, ptrdiff_t, T const * , T const & > {
    public:
        //using iterator_category = std::bidirectional_iterator_tag;
        //using value_type        = T;
        //using difference_type   = ptrdiff_t;
        //using pointer           = T const*;
        //using reference         = T const&;
        using Self = __const_edgeIterator;
        __const_edgeIterator()
            : m_ptr(nullptr)
        {}
        __const_edgeIterator( __const_edgeIterator const& i)
            : m_ptr( i.m_ptr )
        {
        }
        __const_edgeIterator(__d_link<typename std::remove_cv<T>::type >* ptr)
            : m_ptr( ptr )
        {
        }
        __const_edgeIterator& operator=( __const_edgeIterator const& i){
            if(this != &i ){
                m_ptr = i.m_ptr;
            }
            return *this;
        }
        bool operator==(const Self& x) const {
            return m_ptr == x.m_ptr;
        }
        bool operator != (const Self& x) const {
            return m_ptr != x.m_ptr;
        }
        reference operator* () const {
            pointer ptr = static_cast<pointer>(m_ptr);
            return *ptr;
        }
        pointer operator->() const {
            pointer ptr = static_cast<pointer>(m_ptr);
            return ptr;
        }
        Self& operator++() {
            m_ptr = m_ptr->getNext( );
            return *this;
        }
        Self operator++(int) {
            Self tmp = *this;
            ++(*this);
            return tmp;
        }
        Self& operator--() {
            m_ptr = m_ptr->getPre();
            return *this;
        }
        Self operator--(int) {
            Self tmp = *this;
            --(*this);
            return tmp;
        }
    private:
        __d_link<Edge> const* m_ptr;
    };
*/
    using const_edgeIterator = __edgeIterator<Edge,true>;


    adjacency_list() {
    }
    adjacency_list(adjacency_list const&) = delete;
    adjacency_list& operator=(adjacency_list const&) = delete;
    adjacency_list(adjacency_list&& al) {
        super::m_container = std::move(al.super::m_container);
        m_predecessor = std::move(al.m_predecessor);
        m_successor = std::move(al.m_successor);
    }
    adjacency_list& operator=(adjacency_list&& al) {
        if (this != &al) {
            super::m_container = std::move(al.super::m_container);
            m_predecessor = std::move(al.m_predecessor);
            m_successor = std::move(al.m_successor);
        }
        return *this;
    }

    vertexIterator vertexBegin(){
        return super::m_container.begin();
    }

    vertexIterator vertexEnd(){
        return super::m_container.end();
    }

    const_vertexIterator vertexBegin() const{
        return super::m_container.begin();
    }

    const_vertexIterator vertexEnd() const{
        return super::m_container.end();
    }

    size_t vertexSize() const{
        return super::m_container.size();
    }
    template<typename ... _Args>
    Edge * add_edge( Vertex * v1, Vertex *v2, _Args && ... args ){
        if( nullptr == v1 || nullptr == v2){
            return nullptr;
        }
        else{
            Edge *retEdge = nullptr;
            auto iter =m_successor.find(v1);
            if( iter == m_successor.end() ){
                auto dlink = _InsertLinkHead_Successor( v1);
                retEdge = _InsertEdge( dlink, v1,v2, std::forward<_Args>(args) ... );
            }
            else{
                retEdge = _InsertEdge( iter->second, v1,v2, std::forward<_Args>(args) ... );
            }
            _Add_predecessorEdge(v2, v1);
            return retEdge;
        }
    }

    edgeIterator edgeBegin( Vertex* v){
        auto iter = m_successor.find( v );
        if( iter != m_successor.end() ){
            return edgeIterator(iter->second->getNext());
        }
        return edgeIterator( );
    }

    edgeIterator edgeEnd( Vertex* v){
        auto iter = m_successor.find( v );
        if( iter != m_successor.end() ) {
            return edgeIterator(iter->second);
        }
        return edgeIterator( );
    }

    const_edgeIterator edgeBegin( Vertex* v) const{
        auto iter = m_successor.find( v );
        if( iter != m_successor.end() ) {
            return const_edgeIterator(iter->second->getNext());
        }
        return const_edgeIterator( );
    }

    const_edgeIterator edgeEnd( Vertex * v) const{
        auto iter = m_successor.find( v );
        if( iter != m_successor.end() ) {
            return const_edgeIterator(iter->second);
        }
        return const_edgeIterator( );
    }
    
    edgeIterator preEdgeBegin( Vertex* v){
        auto iter =m_predecessor.find( v );
        if( iter !=m_predecessor.end() ){
            return edgeIterator(iter->second->getNext());
        }
        return edgeIterator( );
    }

    edgeIterator preEdgeEnd( Vertex* v){
        auto iter = m_predecessor.find( v );
        if( iter != m_predecessor.end() ) {
            return edgeIterator(iter->second);
        }
        return edgeIterator( );
    }

    const_edgeIterator preEdgeBegin( Vertex* v) const{
        auto iter = m_predecessor.find( v );
        if( iter != m_predecessor.end() ) {
            return const_edgeIterator(iter->second->getNext());
        }
        return const_edgeIterator( );
    }

    const_edgeIterator preEdgeEnd( Vertex * v) const{
        auto iter = m_predecessor.find( v );
        if( iter != m_predecessor.end() ) {
            return const_edgeIterator(iter->second);
        }
        return const_edgeIterator( );
    }

private:
    __d_link<Edge>* _InsertLinkHead_Successor( Vertex * vertex ){
        __d_link<Edge>* e = new __d_link<Edge>( );
        e->m_next = static_cast<Edge*>(e);
        e->m_pre  = static_cast<Edge*>(e);
        m_successor.insert( std::make_pair( vertex, e ));
        return e;
    }
    __d_link<edge<Vertex>>* _InsertLinkHead_Predecessor(Vertex* vertex) {
        __d_link < edge<Vertex> >* e = new __d_link<edge<Vertex>>();
        e->m_next = static_cast<edge<Vertex>*>(e);
        e->m_pre  = static_cast<edge<Vertex>*>(e);
        m_predecessor.insert(std::make_pair(vertex, e));
        return e;
    }
    edge<Vertex>* _Add_predecessorEdge(Vertex* v1, Vertex* v2) {
        if (nullptr == v1 || nullptr == v2) {
            return nullptr;
        }
        else {
            edge<Vertex>* retEdge = nullptr;
            auto iter = m_predecessor.find(v1);
            if (iter == m_predecessor.end()) {
                auto dlink = _InsertLinkHead_Predecessor(v1);
                retEdge = _InsertEdge(dlink, v1, v2);
            }
            else {
                retEdge = _InsertEdge(iter->second, v1, v2);
            }

            return retEdge;
        }
    }

    template<typename T,typename ... _Args>
    T* _InsertEdge( __d_link<T>* end, Vertex *v1, Vertex* v2, _Args&& ... args){
        T* e = new T( v1,v2 ,std::forward<_Args>(args)...);
        if( e == nullptr)
            return e;
        T * pre = end->getPre();
        pre->m_next = e;
        e->m_pre    = pre;
        e->m_next   = static_cast<T*>(end);
        end->m_pre  = e;
        return e;
    }

private:
    std::map<Vertex*, __d_link<Edge>* > m_successor; /// 现在边的结构时双向链表连接起来的,我们可以使用 set来保存边
    std::map<Vertex*, __d_link<edge<Vertex>>*>  m_predecessor;
};



}
