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
	{
	
	}



	void Value::addUser(Value* v) {
		m_users.appendUser(v);
	}

	Users const& Value::getUsers() const {
		return m_users;
	}
}