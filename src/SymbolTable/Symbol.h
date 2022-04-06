#pragma once
#include <string_view>
namespace ENV {
	enum SymbolType {
		kVariable,
		kFunction,
		kType,

	};

	class Symbol {
	public:
		Symbol(SymbolType type, std::string_view name);
		SymbolType       getSymbolType() const;
		std::string_view getSymbolName() const;
	private:
		SymbolType m_type;
		std::string_view m_name;
	};
}