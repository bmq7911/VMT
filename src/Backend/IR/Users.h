#pragma once
#include <list>
namespace IR {
	class Value;
	class Users {
	public:
		using iterator = std::list<Value*>::iterator;
		using const_iterator = std::list<Value*>::const_iterator;
		iterator begin() {
			return m_UsersList.begin();
		}
		iterator end() {
			return m_UsersList.end();
		}
		const_iterator cbegin() const{
			return m_UsersList.cbegin();
		}
		const_iterator cend() const{
			return m_UsersList.cend();
		}
		void appendUser(Value* value) {
			m_UsersList.emplace_back(value);
		}
		bool empty() const{
			return m_UsersList.empty( );
		}
		size_t size() const {
			return m_UsersList.size( );
		}
	private:
		std::list<Value*> m_UsersList;
	};
}