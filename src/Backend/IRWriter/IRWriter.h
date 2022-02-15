#pragma once
#include "Backend/IR/IRContext.h"
#include "Backend/IRWriter/IIRWriteVisitor.h"
#include <ostream>

namespace IR {
	class Function;
	class Instruction;
	class IRWriter {
	public:
		IRWriter(std::shared_ptr<IRContext> context);
		IRWriter& write(IR::Function* function,std::ostream &os );
	private:
		IRWriter& _WriteFunction(IR::Function* function, std::ostream& os);
	private:
		std::shared_ptr<IRContext> m_context;
	};

}