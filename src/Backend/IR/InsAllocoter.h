#pragma once
#include <stdlib.h>

namespace IR {
    template<typename T, typename ... Args >
    T* ctor(void * ptr, Args &&...  args) {
        return new (ptr) T( std::forward<Args>(args)...);
    }
    
    template<typename T>
    void dctor(T * ptr) {
        ptr->~T();
    }


    template<typename T>
    class allocator {
    public:
        template<typename ... Args>
        T* alloc(Args && ... args) {
            void * ptr = malloc(sizeof(T));
            if (nullptr == ptr)
                return nullptr;
            else
                return ctor<T, Args...>(ptr,std::forward<Args>(args) ...);
        }
        
    };
}