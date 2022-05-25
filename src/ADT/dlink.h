#pragma once
#include <type_traits>
namespace ADT {
	template<typename T>
	class d_link {
	public:
		d_link() 
			: m_next( nullptr )
			, m_pre( nullptr )
		{

		}
		T* get_next() {
			return m_next;
		}
		T* get_pre() {
			return m_pre;
		}
		void insert_back( T * v) {
			if (nullptr != m_next) {
				v->m_next = m_next;
				v->m_pre = static_cast<T*>(this);
				this->m_next->m_pre = v;
				this->m_next = v;
			}
			else {
				this->m_next = v;
				v->m_pre = static_cast<T*>(this);
			}
		}
		void insert_front( T * v) {
			if (nullptr != m_pre) {
				this->m_pre->m_next = v;
				v->m_pre = this->m_pre;
				this->m_pre = v;
				v->m_next = static_cast<T*>(this);
			}
			else {
				this->m_pre = v;
				v->m_next = static_cast<T*>(this);
			}
		}

		template<typename ... _Args>
		void insert_back( _Args&& ...args ) {
			T* v = new T(std::forward<_Args>(args) ...);
			if (nullptr != m_next) {
				v->m_next = m_next;
				v->m_pre = this;
				this->m_next->m_pre = v;
				this->m_next = v;
			}
			else {
				this->m_next = v;
				v->m_pre = this;
			}
		}
		template<typename ... _Args>
		void insert_front( _Args&& ... args) {
			T* v = new T(std::forward<_Args>(args) ...);
			if (nullptr != m_pre) {
				this->m_pre->m_next = v;
				v->m_pre = this->m_pre;
				this->m_pre = v;
				v->m_next = this;
			}
			else {
				this->m_pre = v;
				v->m_next = this;
			}
		}
	private:
		T* m_next;
		T* m_pre;
	};
}