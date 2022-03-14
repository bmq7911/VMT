#include "Backend/IRWriter/TextIRWriteVisitor.h"
#include "Backend/IR/Value.h"
#include "Backend/IR/Constant.h"
#include "Backend/IR/Type.h"
#include "Backend/IR/Function.h"

#include <sstream>

namespace IR {
	void  TextIRWriteVisitor::dispatchIns(IR::Instruction* ins) {
		IR::Instruction::OpCode op = ins->getOpCode();
		switch (op) {
#define EMIT_IR_INS(x,name,...) case IR::Instruction::OpCode::k##name:{ write##name(ins); }break;
#include "Backend/IR/IROpCode.inl"
#undef EMIT_IR_INS
		default:
			break;
		}
	}

	void TextIRWriteVisitor::writeFunction(IR::Function* func) {
		m_ss << "func" << func->getFunctionName() << "(";
		for (size_t i = 0; i < func->getArgsSize(); ++i) {
			Value* v = func->getArgsAt(i);
			m_ss << _GetTypeName(v->getType()) << ":" << v->getValueName();
			if (i != func->getArgsSize() - 1) {
				m_ss << ", ";
			}
		}
		m_ss << ")->" << _GetTypeName(func->getFunctionType()->getReturnType()) << "\r\n{\r\n";
		for (auto iter = func->begin(); iter != func->end(); iter = iter->getNext()) {
			dispatchIns(iter);
		}
		m_ss << "\r\n}\r\n";
	}

	std::string TextIRWriteVisitor::getTextStr() const {
		return m_ss.str();
	}

	std::string TextIRWriteVisitor::getInsAsmString() const {
		return m_ss.str();
	}
	void TextIRWriteVisitor::writeJmp(IR::Instruction* ins) {
		IR::Jmp* jmp = static_cast<IR::Jmp*>( ins );
		m_ss << "\t"<< jmp->getOpStr()<<" " << jmp->getJmpLabel() << "\r\n";
		
	}
	void TextIRWriteVisitor::writeBr(IR::Instruction* ins) {
		IR::Br* br = static_cast<IR::Br*>(ins);
		m_ss << "\t"<< br->getOpStr()<<" " << _GetTypeNamePair(br->getCmpValue()) << " label:" << br->getTrueLabel() << "	label:" << br->getFalseLabel() << "\r\n";
	}

	void TextIRWriteVisitor::writeCall(IR::Instruction* ins) {
		
	}

	void TextIRWriteVisitor::writeRet(IR::Instruction* ins) {
		IR::Ret* ret = static_cast<IR::Ret*>(ins);
		Value* retValue = ret->getInsRetValue();
		if (nullptr != retValue)
			m_ss << "\t" << ret->getOpStr() << " " << _GetTypeNamePair(retValue) << "\r\n";
	}

	void TextIRWriteVisitor::writeSin(IR::Instruction* ins) {
		_WriteUnaryIns( static_cast<IR::UnaryOpIns*>(ins));
	}
	void TextIRWriteVisitor::writeCos(IR::Instruction* ins) {
		_WriteUnaryIns(static_cast<IR::UnaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeTan(IR::Instruction* ins) {
		_WriteUnaryIns(static_cast<IR::UnaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeExp(IR::Instruction* ins) {
		_WriteUnaryIns(static_cast<IR::UnaryOpIns*>(ins));
	}
	void TextIRWriteVisitor::writeLog(IR::Instruction* ins) {
		_WriteUnaryIns(static_cast<IR::UnaryOpIns*>(ins));
	}
	void TextIRWriteVisitor::writeNot(IR::Instruction* ins) {
		_WriteUnaryIns(static_cast<IR::UnaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeT(IR::Instruction* ins) {
		_WriteUnaryIns(static_cast<IR::UnaryOpIns*>(ins));
	}


	void TextIRWriteVisitor::writeInvert(IR::Instruction* ins) {
		_WriteUnaryIns(static_cast<IR::UnaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeBitNegate(IR::Instruction* ins) {
		_WriteUnaryIns(static_cast<IR::UnaryOpIns*>(ins));
	}

	
	void TextIRWriteVisitor::writeAdd(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}
	
	void TextIRWriteVisitor::writeMinus(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}
	void TextIRWriteVisitor::writeMul(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeDiv(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeMod(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}
	void TextIRWriteVisitor::writeDotAdd(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}


	void TextIRWriteVisitor::writeDotMinus(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}
	
	void TextIRWriteVisitor::writeDotMul(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeDotDiv(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeDotMod(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeAnd(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeOr(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeXor(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}


	void TextIRWriteVisitor::writeBitAnd(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeBitOr(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeBitXor(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeDot(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeLength2(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeCross(IR::Instruction* ins) {
		_WriteBinaryIns(static_cast<IR::BinaryOpIns*>(ins));
	}

	void TextIRWriteVisitor::writeAlloc(IR::Instruction* ins) {
		auto allocIns = static_cast<AllocIns*>(ins);
		Value* value = allocIns->getFirstOperand();
		if (nullptr != value) {
			m_ss<< "\t" << _GetTypeNamePair(allocIns->getRetValue()) << " = " << allocIns->getOpStr() << " " << _GetTypeNamePair(value) << "\r\n";
		}
		else {
			m_ss << "\t" << _GetTypeNamePair(allocIns->getRetValue()) << " = " << allocIns->getOpStr() << "\r\n";
		}
	}
	
	void TextIRWriteVisitor::writeAssign(IR::Instruction* ins) {
	
	}

	void TextIRWriteVisitor::writeCast(IR::Instruction* ins) {
	
	}

	void TextIRWriteVisitor::writeLabel(IR::Instruction* ins) {
		IR::Label* label = static_cast<IR::Label*>(ins);
		m_ss <<"\r\n"<< label->getLabelName() << ":\r\n";
	}

	void TextIRWriteVisitor::writeError(IR::Instruction* ins) {
	
	}


	void TextIRWriteVisitor::_WriteBinaryIns(IR::BinaryOpIns* ins ) {
		m_ss << "\t" << _GetTypeNamePair(ins->getRetValue()) << " = " << ins->getOpStr() << " " << _GetTypeNamePair(ins->getFirstOperand()) << "	" << _GetTypeNamePair(ins->getSecondOperand());
		m_ss << "\r\n";
	}

	void TextIRWriteVisitor::_WriteUnaryIns(IR::UnaryOpIns* ins) {
		m_ss << "\t" << _GetTypeNamePair(ins->getRetValue()) << " = " << _GetTypeNamePair(ins->getFirstOperand())<< "\r\n";
	}
	std::string TextIRWriteVisitor::_GetTypeNamePair(IR::Value* value) const {
		if (true == value->isLocal()) {
			return _GetTypeName( value->getType()) + ":%" + value->getValueName();
		}
		else {
			return _GetTypeName( value->getType()) + ":@" + value->getValueName();
		}
	}
	std::string TextIRWriteVisitor::_GetTypeNamePair(IR::Constant const* constantValue) const {
		return _GetTypeName( constantValue->getType() ) + ":" + constantValue->getValueStr();
	}

	std::string TextIRWriteVisitor::_GetTypeName(IR::Type const* type) const {
		if (true == type->isBoolType()) {
			return "bool";
		}
		else if (true == type->isIntegerType()) {
			IR::IntegerType const* integerType = static_cast<IR::IntegerType const*>(type);
			uint32_t size = integerType->getSize();
			return std::string("i") + std::to_string(size);
		}
		else if (true == type->isFloatType()) {
			IR::FloatType const* floatType = static_cast<IR::FloatType const*>(type);
			uint32_t size = floatType->getSize();
			return std::string("f") + std::to_string( size );
		}
		else {
			return "";
		}
	}
}