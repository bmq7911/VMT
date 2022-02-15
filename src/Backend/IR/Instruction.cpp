#include "Backend/IR/Instruction.h"
#include "Type.h"
#include "Backend/IR/Function.h"

namespace IR {
    bool Instruction::isUnaryOp( ) const {
        return isUnaryOp(m_Op);
    }

    bool Instruction::isBinaryOp( ) const {
        return isBinaryOp(m_Op);
    }
    InstructionType Instruction::getInsType() const {
        return getInsType(m_Op);
    }
	
    bool Instruction::isUnaryOp(Instruction::OpCode op) {
#define RANGE_ARITHMETIC_IR_INSTRUCTION
#include "Backend/IR/IROpCode.inl"
        uint32_t opCode = static_cast<uint32_t>(op);
        if (UnaryIRInsBeg <= opCode && opCode <= UnaryIRInsEnd)
            return true;
        return false;
#undef  RANGE_ARITHMETIC_IR_INSTRUCTION
    }

    bool Instruction::isBinaryOp(Instruction::OpCode op) {
#define RANGE_ARITHMETIC_IR_INSTRUCTION
#include "Backend/IR/IROpCode.inl"
        uint32_t opCode = static_cast<uint32_t>(op);
        if (BinaryIRInsBeg <= opCode && opCode <= BinaryIRInsEnd)
            return true;
        return false;
#undef  RANGE_ARITHMETIC_IR_INSTRUCTION
    }

    IR::InstructionType Instruction::getInsType(IR::Instruction::OpCode Op) {
#define RANGE_IR_INSTRUCTION
#include "Backend/IR/IROpCode.inl"
#undef  RANGE_IR_INSTRUCTION

        uint32_t opCode = static_cast<uint32_t>(Op);
        if (ControlIRInsBeg <= opCode && opCode <= ControlIRInsEnd) {
            return InstructionType::kControl;
        }
        if (ArithmeticIRInsBeg <= opCode && opCode <= ArithmeticIRInsEnd) {
            return InstructionType::kArithmetic;
        }
		if (MemoryIRInsBeg <= opCode && opCode <= MemoryIRInsEnd) {
			return InstructionType::kMemory;
		}
		if (CastIRInsBeg <= opCode && opCode <= CastIRInsEnd) {
			return InstructionType::kCast;
		}
        if (PseudoIRInsBeg <= opCode && opCode <= PseudoIRInsEnd) {
            return InstructionType::kPseudo;
        }
        return InstructionType::kUnknown;
    }

    const char* Instruction::getOpStr(Instruction::OpCode code) {
        switch (code) {
#define IR_INSTRUCTION_TO_STR
#include "Backend/IR/IROpCode.inl"
#undef  IR_INSTRUCTION_TO_STR
        default:
            return nullptr;
            break;
        }
    }
}

namespace IR {
}