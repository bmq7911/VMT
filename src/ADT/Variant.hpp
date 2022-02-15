#pragma once
#include <stdint.h>
#include <string>

#if __cplusplus < 201103L
#error "this cplusplus version must greater c++11"
#endif /// __cplusplus

namespace ADT{
    struct _dtor {
        virtual ~_dtor(){
        }
    };


    template<typename _T>
    struct _warp_dtor : public _dtor{
        _warp_dtor( _T* ptr ){
            m_ptr = ptr;
        }
        virtual ~_warp_dtor( ){
            m_ptr->~_T();
        }
    private:
        _T* m_ptr;
    };

/// 存在一个最大的问题,就是析构,如何析构
    template<size_t _A, size_t _N,typename _H>
    struct _value_storage_ele{
        _value_storage_ele(){
            new (m_dtor) warp_dtor<_H>( new ( m_ele)_H());
        }
        template<typename _T>
        _T get() const{
            return *(reinterpret_cast<const _T*>(m_ele));
        }

        template<typename _T, typename ... _Args>
        void set( _Args &&... args) {
            _Set<_T>(args...);
        }

        ~_value_storage_ele(){
            _Release();
        }
    private:
        template<typename _T, typename ... _Args>
        void _Set(_Args && ...args){
            _Release();
            new (m_dtor) warp_dtor<_T>( new ( m_ele)_T( std::forward<_Args>(args)...));
        }
        void _Release(){
            reinterpret_cast<dtor*>(m_dtor)->~dtor();
        }
    public:

        alignas(_A) char m_ele[_N];
        alignas(dtor*) char m_dtor[sizeof(dtor*)];
    };


    struct align_info{
        size_t align;
        size_t size;
    };


    template<typename _H, typename ... _Args>
    struct trait_align_info : public trait_align_info<_Args...> {
        using super= trait_align_info<_Args...>;
        constexpr static std::size_t align = alignof(_H) > super::align ? alignof(_H): super::align;//std::max( alignof(_H),std::size_t( super::align) );
        constexpr static std::size_t size = sizeof(_H) > super::size ? sizeof(_H): super::size;//std::max( sizeof(_H), std::size_t( super::size));
    };

    template<typename _T>
    struct trait_align_info<_T>{
        constexpr static std::size_t  align = alignof(_T);
        constexpr static std::size_t  size  = sizeof(_T);

    };

    template<typename _H, typename  ..._Args>
    struct Variant  {
    public:
        constexpr static std::size_t align = trait_align_info<_H,_Args...>::align;
        constexpr static std::size_t size  = trait_align_info<_H,_Args...>::size;

        template<typename _T>
        _T get() const{
            return m_Data.get<_T>();
        }

        template<typename _T,typename... _P>
        void set( _P &&   ...args ) {
            m_Data.set<_T>(args...);
        }
		
		
    private:
		template<typename _T>
        friend _T get( const Value& );
		value_storage_ele_<align, size,_H> m_Data;
    };
}