#include "Backend/IR/Scope.h"
#include "Backend/IR/Value.h"
#include "Backend/IR/Function.h"
#include "Backend/IR/Type.h"

namespace IR {

	Scope::Scope() {
	}
	Scope::Scope(std::shared_ptr<Scope> parent)
		: m_parent(  parent )
	{
	
	}

	std::shared_ptr<Scope>& Scope::getParentScope() {
		return _GetParentScope();
	}

	const std::shared_ptr<Scope>&  Scope::getParentScope() const {
		return _GetParentScope();
	}

	void Scope::insertValue(std::string name, Value* value) {
		auto iter = m_valueNameMap.find(name);
		if (iter == m_valueNameMap.end()) {
			m_valueNameMap.insert(std::make_pair(name, std::list<Value*>{}));
			insertValue(name, value);
		}
		else {
			/// <summary>
			///
			auto beg = iter->second.begin();
			auto end = iter->second.end();
			size_t size = std::distance(beg, end);
			value->setNameIndex(size);
			iter->second.push_front(value);
		}
	
	}
	Scope::iterator  Scope::valueBegin(std::string const& strName) {
		auto iter = m_valueNameMap.find(strName);
		if (iter == m_valueNameMap.end()) {
			return Scope::iterator();
		}
		else {
			return iter->second.begin( );
		}
	}
	Scope::const_iterator Scope::valueBegin(std::string const& strName) const {
		auto iter = m_valueNameMap.find(strName);
		if (iter == m_valueNameMap.end()) {
			return Scope::iterator();
		}
		else {
			return iter->second.begin( );
		}

	}
	Scope::iterator  Scope::valueEnd(std::string const& strName) {
		auto iter = m_valueNameMap.find(strName);
		if (iter == m_valueNameMap.end()) {
			return Scope::iterator();
		}
		else {
			return iter->second.end( );
		}

	}
	Scope::const_iterator Scope::valueEnd(std::string const& strName) const{
		auto iter = m_valueNameMap.find(strName);
		if (iter == m_valueNameMap.end()) {
			return Scope::iterator();
		}
		else {
			return iter->second.end();
		}
	}
	Value* Scope::findValueByName(char const * strName) const{
		if (nullptr == strName)
			return nullptr;
		return _FindValueByName(strName);
	}
	
	Value* Scope::findValueByName(std::string const& strName) const {
		return _FindValueByName(strName);
	}

	Value* Scope::genValueByName(std::string const& strName, IR::Type const* type) {
		Value* value = new Value(strName.c_str(), type, nullptr);
		insertValue(strName, value);
		return value;
	}
	Function* Scope::findFunctionByName(char const* strName) const {
		if (nullptr != strName)
			return nullptr;
		return _FindFunctionByName(strName);
	}

	Function* Scope::findFunctionByName(std::string const& strName) const {
		return _FindFunctionByName(strName);
	}

	std::shared_ptr<Scope>& Scope::_GetParentScope() {
		return m_parent;
	}
	
	const std::shared_ptr<Scope>& Scope::_GetParentScope()const {
		return m_parent;
	}
	/// <summary>
	/// </summary>
	/// <param name="strName"></param>
	/// <returns></returns>
	Value* Scope::_FindValueByName(std::string const& strName) const {
		for (const Scope* p = this; nullptr != p; p = p->_GetParentScope().get()) {
			auto iter = p->_GetValuesMap( ).find(strName);
			if (iter == p->_GetValuesMap().end() ) {
				continue;
			}
			else {
				auto beg = iter->second.begin();
				auto end = iter->second.end();
				if (beg == end)
					return nullptr;
				return *beg;
			}
		}
		return nullptr;
	}

	Function* Scope::_FindFunctionByName(std::string const& strName) const {
		for (const Scope* p = this; nullptr != p; p = p->_GetParentScope().get()) {
			auto iter = p->_GetFunctionsMap().find(strName);
			if (iter == p->_GetFunctionsMap().end()) {
				continue;
			}
			else {
				return iter->second;
			}
		}
		return nullptr;
	}
	std::map<std::string, std::list<Value*>> const& Scope::_GetValuesMap() const {
		return m_valueNameMap;
	}
	std::map<std::string, Function*> const& Scope::_GetFunctionsMap() const {
		return m_functions;
	}
}