#pragma once
#include "Backend/IRWriter/IRWriter.h"
#include "Backend/IRWriter/TextIRWriteVisitor.h"

#include "Backend/IR/IRContext.h"
#include "Backend/IR/Function.h"
#include "Backend/IR/Instruction.h"

namespace IR {

	IRWriter::IRWriter(std::shared_ptr<IRContext> context) 
		: m_context( context )
	{
	
	}
	
	IRWriter& IRWriter::write(IR::Function* function,std::ostream & os ) {
		return _WriteFunction(function, os);
	}


	IRWriter& IRWriter::_WriteFunction(IR::Function* function, std::ostream& os) {
		
		IR::TextIRWriteVisitor insWriter;
		insWriter.writeFunction( function);
		os << insWriter.getTextStr();
		return *this;
	}
}