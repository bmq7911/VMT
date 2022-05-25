#include "Backend/IR/Value.h"

namespace IR {
	Value::Value( char const* name, Type const* type, Instruction* ins) 
		: m_name( name )
		, m_type( type )
		, m_ins( ins )
		, m_bLocal( true )
		, m_bConstant( false )
		, m_bVolatile( false )
		, m_bStatic( false )
		, m_nameIndex( 0 )
	{
	
	}
	Value* Value::clone() {
		Value* new_value = new Value(m_name.c_str( ), m_type, nullptr);
		if (nullptr != new_value) {
			new_value->m_bLocal = m_bLocal;
			new_value->m_bConstant = m_bConstant;
			new_value->m_bVolatile = m_bVolatile;
			new_value->m_bStatic = m_bStatic;
			new_value->m_nameIndex = m_nameIndex;
		}
		return new_value;
	}



	void Value::addUser(Value* v) {
		m_users.appendUser(v);
	}

	Users const& Value::getUsers() const {
		return m_users;
	}
}