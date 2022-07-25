#pragma once
#include <stdint.h>
#include <iterator>
namespace ADT {
	template<typename _T>
	class rbtree {
	public:
		enum color : uint8_t{
			color_red,
			color_black,
		};
		class node_ {
		public:
			node_() 
				: m_lpParent( nullptr )
				, m_lpLeft( nullptr )
				, m_lpRight( nullptr )
				, m_rb( color_red )
			{ }

			node_(color) 
				: m_lpParent( nullptr)
				, m_lpLeft( nullptr)
				, m_lpRight( nullptr)
				. m_rb( color_black)
			{ }
			color getColor() const {
				return m_rb;
			}
			void setColor( color c ) {
				m_rb = c;
			}
			node_* getParent() const {
				return m_lpParent;
			}
			void setParent(node_* nodeptr) {
				m_lpParent = nodeptr;
			}
			node_* getLeft() const {
				return m_lpLeft;
			}
			void setLeft(node_* nodeptr) {
				m_lpLeft = nodeptr;
			}
			node_* getRight() const {
				return m_lpRight;
			}
			void setRight( node_* nodeptr) {
				return m_lpRight;
			}


		private:
			node_* m_lpParent;
			node_* m_lpLeft;
			node_* m_lpRight;
			color m_rb;
		};
		class node : public node_ {
		public:
			node(T&& d)
				: node_( )
				, m_data( d )
			{ }
			node(color c, T&& d)
				: node_(c)
				, m_data( d )
			{ }

			_T& data() {
				return m_data;
			}
			_T const& data() const {
				return m_data;
			}
		private:
			_T m_data;
		};
	public:
		rbtree() 
			: m_root( nullptr )
			, m_leaf( )
		{}
		struct iterator : public std::iterator< std::bidirectional_iterator_tag ,_T>{
		public:
			
		private:
			node* ptr;
		};
		
		iterator insert(_T&& data) {
		
		}
		template<typename ... _Args>
		iterator insert( _Args ... && args) {
		
		}
	private:
		void _RightRotate(node_* node ) {
			
		}
		void _LeftRotate(node_* x) {
			auto y = x->getRight();
			x->setRight(y->getLeft());
			if (nullptr != y->geteft()) {
				y->getLeft()->setParent(x);
			}
			y->setParent( x->getParent() );
		}
		node *_Find( _T const & data ) {
			auto ptr = m_root;
			while (ptr) {
				if (data < ptr->data()) {
					ptr = ptr->getLeft();
				}
				else {
					ptr = ptr->getRight();
				}
				if (ptr == &m_leaf) {
					
				}
			}
		}

	private:
		node* m_root;
		//node_ m_leaf;
	};

}