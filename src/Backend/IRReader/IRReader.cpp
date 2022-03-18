#pragma once
#include "Backend/IRReader/IRReader.h"

#include "Backend/IR/IRContext.h"
#include "Backend/IR/Function.h"
#include "Backend/IR/Instruction.h"

namespace IR {

	IRReader::IRReader(std::shared_ptr<IRContext> context) 
		: m_context( context )
	{
	
	}
	
	IRReader& IRReader::write(IR::Function* function,std::ostream & os ) {
		return _WriteFunction(function, os);
	}


	IRReader& IRReader::_WriteFunction(IR::Function* function, std::ostream& os) {
		
		return *this;
	}
}