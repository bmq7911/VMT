#include "Backend/IR/Scope.h"
#include "Backend/IR/Value.h"
#include "Backend/IR/Function.h"

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

	Value* Scope::findValueByName(char const * strName) const{
		if (nullptr == strName)
			return nullptr;
		return _FindValueByName(strName);
	}
	
	Value* Scope::findValueByName(std::string const& strName) const {
		return _FindValueByName(strName);
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
	Value* Scope::_FindValueByName(std::string const& strName) const {
		for (const Scope* p = this; nullptr != p; p = p->_GetParentScope().get()) {
			auto iter = p->_GetValuesMap( ).find(strName);
			if (iter == p->_GetValuesMap().end() ) {
				continue;
			}
			else {
				return iter->second;
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
	std::map<std::string, Value*> const& Scope::_GetValuesMap() const {
		return m_values;
	}
	std::map<std::string, Function*> const& Scope::_GetFunctionsMap() const {
		return m_functions;
	}
}