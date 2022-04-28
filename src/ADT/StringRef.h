#pragma once
#include <stdint.h>
#include <cstring>
#include <string>

namespace ADT {
    class StringRef {
    public:
        StringRef() 
            : m_ptr(nullptr)
            , m_length( 0)
        {}
        StringRef( const char * ptr, uint32_t length)
            :m_ptr( ptr)
            ,m_length(length)
        {
        }
        StringRef( const char* ptr)
            :m_ptr(ptr)
        {
            m_length = std::strlen(ptr);
        }
        StringRef(StringRef const& ref) 
            :m_ptr (ref.m_ptr)
            ,m_length( ref.m_length)
        {}
        StringRef& operator=( StringRef const& ref) {
            if (this != &ref) {
                m_ptr = ref.m_ptr;
                m_length = ref.m_length;
            }
            return *this;
        }
        StringRef(StringRef && ref) {
            m_ptr = ref.m_ptr;
            m_length = ref.m_length;
            ref.m_ptr = nullptr;
            ref.m_length = 0;
        }
        StringRef& operator=(StringRef && ref) {
            if (this != &ref) {
                m_ptr = ref.m_ptr;
                m_length = ref.m_length;
                ref.m_ptr = nullptr;
                ref.m_length = 0;
            }
            return *this;
        }

        operator bool() const {
            return (nullptr != m_ptr && 0 != m_length);
        }
        std::string to_string() const;
        
    private:
        const char * m_ptr;
        uint32_t m_length;

    };
}
