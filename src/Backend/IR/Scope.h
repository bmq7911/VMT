#pragma once
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <map>
namespace IR {
	/// <summary>
	/// 
	/// </summary>
	class Value;
	class Function;
	class Type;

	class Scope {
	public:
		using iterator       = std::list<Value*>::iterator;
		using const_iterator = std::list<Value*>::const_iterator;

		Scope();
		Scope(std::shared_ptr<Scope>);
		std::shared_ptr<Scope>& getParentScope();
		const std::shared_ptr<Scope>& getParentScope() const;
		void insertValue(std::string name, Value* value);
		iterator  valueBegin( std::string const& strName);
		const_iterator valueBegin( std::string const& strName) const;
		iterator  valueEnd(std::string const& strValue);
		const_iterator valueEnd(std::string const& strName) const;
		Value*    findValueByName(const char* strName) const;
		Value*    findValueByName(std::string const& strName) const;
		Value*    genValueByName(std::string const& strName, IR::Type const* type );
		Function* findFunctionByName(const char* strName) const;
		Function* findFunctionByName(std::string const& strName) const;
	private:
		std::shared_ptr<Scope>&       _GetParentScope();
		const std::shared_ptr<Scope>& _GetParentScope()const;
		Value*    _FindValueByName(std::string const& strName) const;
		Function* _FindFunctionByName(std::string const& strName) const;
		std::map<std::string, std::list<Value*>> const&  _GetValuesMap() const;
		std::map<std::string, Function*> const&          _GetFunctionsMap() const;
	private:
		std::shared_ptr<Scope>                       m_parent;
		std::map<std::string, std::list<Value*> >    m_valueNameMap;
		std::map<std::string, Function*>             m_functions;
	};
}
