#pragma once
#include "Backend/IR/Instruction.h"
#include "Backend/IRWriter/IIRWriteVisitor.h"
#include <sstream>

namespace IR {

	class TextIRWriteVisitor : public IIRWriteVisitor{
	public:
		void dispatchIns(IR::Instruction* ins) override;
		void writeFunction(IR::Function* func) override;
		std::string getTextStr() const;
	private:
		std::string getInsAsmString() const;
#define EMIT_IR_INS(x,name,...) void write##name( IR::Instruction* ins );
#include "Backend/IR/IROpCode.inl"
#undef EMIT_IR_INS
	private:

		void _WriteBinaryIns(IR::BinaryOpIns* ins);
		void _WriteUnaryIns(IR::UnaryOpIns* ins);

		std::string _GetTypeNamePair(IR::Value* value) const;
		std::string _GetTypeNamePair(IR::Constant const* constantValue) const;
		std::string _GetTypeName(IR::Type const * type) const;
	private:
		std::stringstream m_ss;
	};

}