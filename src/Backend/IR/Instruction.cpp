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

    bool Instruction::isInsHaveResult(Instruction::OpCode op) {
        switch ( op) {
#define EMIT_IR_INS(x, name, haveRet,...) case Instruction::OpCode::k##name: return haveRet;break;
#include "Backend/IR/IROpCode.inl"
#undef EMIT_IR_INS
        default:
            return false;
            break;
        }
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

    Instruction::OpCode Instruction::getOpCode(std::string_view const& view) {
        static std::map<std::string_view, Instruction::OpCode> __s_maps;
        if (__s_maps.empty()) {
#define EMIT_IR_INS(x,name, haveRet,...) __s_maps.insert( std::make_pair(std::string_view(#name), Instruction::OpCode::k##name ) );
#include "Backend/IR/IROpCode.inl"
#undef EMIT_IR_INS
        }
        auto iter = __s_maps.find(view);
        if (iter == __s_maps.end()) {
            return Instruction::OpCode::kError;
        }
        return iter->second;
    }
}

namespace IR {
}