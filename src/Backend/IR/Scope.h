#pragma once
#include <memory>
#include <vector>
#include <string>
#include <map>
namespace IR {
	/// <summary>
	/// 
	/// </summary>
	class Value;
	class Function;
	class Scope {
	public:
		Scope();
		Scope(std::shared_ptr<Scope>);
		std::shared_ptr<Scope>& getParentScope();
		const std::shared_ptr<Scope>& getParentScope() const;
		Value*    findValueByName(const char* strName) const;
		Value*    findValueByName(std::string const& strName) const;
		Function* findFunctionByName(const char* strName) const;
		Function* findFunctionByName(std::string const& strName) const;
	private:
		std::shared_ptr<Scope>&       _GetParentScope();
		const std::shared_ptr<Scope>& _GetParentScope()const;
		Value*    _FindValueByName(std::string const& strName) const;
		Function* _FindFunctionByName(std::string const& strName) const;
		std::map<std::string, Value*> const&    _GetValuesMap() const;
		std::map<std::string, Function*> const& _GetFunctionsMap() const;
	private:
		std::shared_ptr<Scope> m_parent;
		std::map<std::string, Value*>   m_values;
		std::map<std::string, Function*> m_functions;
	};
}
