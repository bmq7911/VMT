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
		T* getNext() {
			return m_next;
		}
		T* getPre() {
			return m_pre;
		}
		void insertBack( T * v) {
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
		void insertFront( T * v) {
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
		void insertBack( _Args&& ...args ) {
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
		void insertFront( _Args&& ... args) {
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