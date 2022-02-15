#pragma once
#include "Backend/IR/Value.h"

namespace IR {
	class Variable : public Value {
	public:
		Variable(const char* name, Type const* type, Instruction* ins)
			:Value( name, type, ins) 
		{
			
		}
	};
}