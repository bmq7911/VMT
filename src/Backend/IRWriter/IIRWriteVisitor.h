#pragma once
#include "Backend/IR/Instruction.h"
#include <sstream>

namespace IR {
	
	struct IIRWriteVisitor {
	public:
		virtual void dispatchIns(IR::Instruction* ins) = 0;
		virtual void writeFunction(IR::Function* func) = 0;
	};
	
}