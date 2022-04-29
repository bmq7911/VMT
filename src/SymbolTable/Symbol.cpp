#include "SymbolTable/Symbol.h"

namespace ENV {
	Symbol::Symbol(SymbolType type, std::string_view name) 
		: m_type( type )
		, m_name( name )
	{}
	SymbolType Symbol::getSymbolType() const {
		return m_type;
	}
	std::string_view Symbol::getSymbolName() const {
		return m_name;
	}

}