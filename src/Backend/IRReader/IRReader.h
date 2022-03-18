#pragma once
#include "Backend/IR/IRContext.h"
#include "Backend/IRWriter/IIRWriteVisitor.h"
#include <ostream>

namespace IR {
	class Function;
	class Instruction;
	
	class IRReader {
	public:
		IRReader(std::shared_ptr<IRContext> context);
		IRReader& write(IR::Function* function,std::ostream &os );
	private:
		IRReader& _WriteFunction(IR::Function* function, std::ostream& os);
	private:
		std::shared_ptr<IRContext> m_context;
	};

}