#pragma once
#include <type_traits>
namespace ADT{
    template< bool >
    class enable;
    template<>
    class enable<true> {
    };

	template<typename T>
	class list_node  {
        template<typename T1, typename U1>
        friend class plist;
	public:
        list_node()
            : prev(nullptr)
            , next(nullptr)
        {
        }
		const T* getPrev() const{
			return prev;
		}
		T* getPrev() {
			return prev;
		}
		
		const T* getNext() const{
			return next;
		}
		
		T* getNext() {
			return next;
		}
		
	private:
		T * prev;
		T * next; 
	};

    template<typename T>
    struct __sentinel{
        T* begin;
        T* end;
    };
	
    template<typename T,
             typename U = typename std::enable_if<std::is_base_of<list_node<T>,T>::value>::type>
    class plist {
    public:

    public:
        plist()
            : m_sentinel( )
        {
            m_sentinel.next = (T*) & m_sentinel;
            m_sentinel.prev = (T*) & m_sentinel;
        }
        T* push_back( T * N) {
            /// <summary>
            /// Пе
            /// </summary>
            /// <param name="N"></param>
            /// <returns></returns>
            if ( m_sentinel.next == nullptr  ) {
                N->prev = (T*)&m_sentinel;
                N->next =(T*)&m_sentinel;
                m_sentinel.next = N;
                m_sentinel.prev = N;
            }
            else {
                insert( end(), N);
            }
            return N;
        }

        T* insert( T* iter, T *N) {
            auto preNode = iter->getPrev();
            preNode->next = N;
            N->prev = preNode;
            N->next = iter;
            iter->prev = N;
            return N;
        }
        T* end() {
            return (T*)&m_sentinel;
        }
        T const* end() const {
            return (T*)&m_sentinel;
        }
        T* begin() {
            return m_sentinel.next;
        }
        T const* begin() const {
            return m_sentinel.next;
        }
        T* first() {
            if (m_sentinel.next == &m_sentinel) {
                return nullptr;
            }
            return m_sentinel.next;
        }
        T const* first() const {
            if (m_sentinel.next == &m_sentinel) {
                return nullptr;
            }
            return m_sentinel.next;
        }
        T* last() {
            if (m_sentinel.prev == &m_sentinel) {
                return nullptr;
            }
            return m_sentinel.prev;
        }
        T const* last() const {
            if (m_sentinel.prev == &m_sentinel) {
                return nullptr;
            }
            return m_sentinel.prev;
        }
        bool empty() const {
            return m_sentinel.first == &m_sentinel;
        }
    private:
        list_node<T> m_sentinel;
    };

}