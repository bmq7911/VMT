#include "Backend/IR/Instruction.h"
#include "Backend/IR/Function.h"
#include "Backend/IR/Type.h"
#include "utils/utils.h"


namespace IR {
    //
    Type const* VoidType::isSupportOp(Instruction::OpCode ) const {
        return nullptr;
    }
}

namespace IR {

    Type const* BoolType::isSupportOp(Instruction::OpCode op) const {
        static const Instruction::OpCode SupportOp[] = {
            Instruction::OpCode::kAnd,
            Instruction::OpCode::kOr,
            Instruction::OpCode::kXor,
        };
        for (size_t i = 0; i < utils::array_size(SupportOp); ++i) {
            if (SupportOp[i] == op)
                return this;
        }

        return nullptr;
    }

}

namespace IR {

    Type const* IntegerType::isSupportOp(Instruction::OpCode op) const {
        static const Instruction::OpCode SupportOp[] = {
            Instruction::OpCode::kAdd,
            Instruction::OpCode::kMinus,
            Instruction::OpCode::kMul,
            Instruction::OpCode::kDiv,
            Instruction::OpCode::kMod,
        };
        for (size_t i = 0; i < utils::array_size(SupportOp); ++i) {
            if (SupportOp[i] == op)
                return this;
        }

        return nullptr;
    }
}

namespace IR {
    Type const* FloatType::isSupportOp(Instruction::OpCode op) const {
        static const Instruction::OpCode SupportOp[] = {
            Instruction::OpCode::kMinus,
            Instruction::OpCode::kSin,
            Instruction::OpCode::kCos,
            Instruction::OpCode::kTan,
        };
        for (size_t i = 0; i < utils::array_size(SupportOp); ++i) {
            if (SupportOp[i] == op)
                return this;
        }
        return nullptr;
    }
}
namespace IR{
    /// 数乘等
    Type const * VectorType::isSupportOp(Instruction::OpCode op) const {
        return nullptr;
        /*
        if (this != v) {
            /// 以矩阵形式看两个向量的乘积
            if ( v->isVectorType()  ) {
                VectorType const* tv = static_cast<VectorType const*>(v);
                if ( (tv->getBasicType() == this->getBasicType() ) || 
                     tv->getDimSize() == this->getDimSize() ) {
                    if (op == Instruction::OpCode::kMul) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
            }
            else {
                /// 数乘形式
                if ( this->getBasicType() == v && Instruction::OpCode::kMul == op) {
                    return true;
                }
            }
            return false;
        }
        else {
            const Type * basicType = this->getBasicType();
            if ( op == Instruction::OpCode::kDot ||
                 op == Instruction::OpCode::kLength2){
                if (basicType->isFloatType()) {
                    return true;
                }
                else {
                    return false;
                }
            }
            if (op == Instruction::OpCode::kCross) {
                if (basicType->isFloatType() && 3 == getDimSize()) {
                    return true;
                }
                else {
                    return false;
                }
            }
            return basicType->isSupportOp(op, basicType);
        }
        return false;
        */
    }
}


namespace IR {
        
        
    Type const* MatrixType::isSupportOp(Instruction::OpCode op ) const {
        return nullptr;
    }

}

namespace IR {

    FunctionType::FunctionType(Type* retType) 
        : m_retType( retType)
    {
    
    }
    void FunctionType::addParamType(Type* type) {
        m_paramsType.push_back(type);
    }
    Type* FunctionType::getReturnType() const {
        return m_retType;
    }
    size_t FunctionType::sizeParamsType() const {
        return m_paramsType.size();
    }
    Type* FunctionType::atParamType(uint32_t i) const {
        if (i < m_paramsType.size()) {
            return m_paramsType.at(i);
        }
        return nullptr;
    }
}