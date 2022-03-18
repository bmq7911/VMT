#pragma once 
#include "Backend/IR/Value.h"

namespace IR {
	class Type;
	class Constant : public Value {
	public:
		Constant( Type const* type)
			: Value( "", type, nullptr)
		{
			m_bLocal = true;
			m_bConstant = true;
			m_bVolatile = false;
			m_bStatic = true;
		}
		virtual std::string getValueStr() const = 0;
	private:
	};

	class IntegerConstant : public Constant {
	public:
		IntegerConstant( Type const* type, uint64_t value)
			: Constant( type)
			, m_value( value )
		{}
		std::string getValueStr() const override {
			return std::to_string(m_value);
		}
	private:
		uint64_t m_value;
	};

	class FloatConstant : public Constant {
	public:
		FloatConstant(Type const* type, float value) 
			: Constant( type )
			, m_value( value )
		{
		}
		FloatConstant(Type const* type, double value) 
			: Constant( type )
			, m_value( value )
		{}
		std::string getValueStr() const override {
			return std::to_string(m_value);
		}
	private:
		float m_value;
	};

	class StringConstant : public Constant {


	};

	class VecConstant : public Constant {

	};

	class MatContant : public Constant {

	};
}