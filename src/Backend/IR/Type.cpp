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
            Instruction::OpCode::kAdd,
            Instruction::OpCode::kMul,
            Instruction::OpCode::kDiv,
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

namespace IR {
    void TypeManger::_InitType() {
#define __IR_INSERT_INTEGER_TYPE(x)\
            auto ptr_i##x = new IntegerType( x );\
            m_typeMap.insert(std::make_pair("i"#x, ptr_i##x ));

        __IR_INSERT_INTEGER_TYPE(8)
            __IR_INSERT_INTEGER_TYPE(16)
            __IR_INSERT_INTEGER_TYPE(32)
            __IR_INSERT_INTEGER_TYPE(64)
            __IR_INSERT_INTEGER_TYPE(128)
            __IR_INSERT_INTEGER_TYPE(256)
            __IR_INSERT_INTEGER_TYPE(512)

#define __IR_INSERT_FLOAT_TYPE(x)\
            auto ptr_f##x = new FloatType( x );\
            m_typeMap.insert(std::make_pair("f"#x, ptr_f##x ));

            __IR_INSERT_FLOAT_TYPE(32)
            __IR_INSERT_FLOAT_TYPE(64)
            __IR_INSERT_FLOAT_TYPE(128)

#define __LINK(x,y) x##_##y
#define __ELINK(x,y) __LINK(x,y)
#define __MERAGE(x,y) x##y
#define __XMERAGE(x,y) __MERAGE(x,y) 

#define _IR_INSERT_VECTOR_TYPE(n,y,x) IR::VectorType* __ELINK(__XMERAGE(__XMERAGE(vec,n),y),x) = new IR::VectorType( x,ptr_##n##y );\
            m_typeMap.insert(std::make_pair("vec<"#n#y","#x">" , __ELINK(__XMERAGE(__XMERAGE(vec,n),y),x) ));


            _IR_INSERT_VECTOR_TYPE(i, 8, 2)
            
            _IR_INSERT_VECTOR_TYPE(i,16,2)
            _IR_INSERT_VECTOR_TYPE(i,32,2)
            _IR_INSERT_VECTOR_TYPE(i,64,2)
            _IR_INSERT_VECTOR_TYPE(i,128,2)
            _IR_INSERT_VECTOR_TYPE(i,256,2)
            _IR_INSERT_VECTOR_TYPE(i,512,2)


            _IR_INSERT_VECTOR_TYPE(i,8,3)
            _IR_INSERT_VECTOR_TYPE(i,16,3)
            _IR_INSERT_VECTOR_TYPE(i,32,3)
            _IR_INSERT_VECTOR_TYPE(i,64,3)
            _IR_INSERT_VECTOR_TYPE(i,128,3)
            _IR_INSERT_VECTOR_TYPE(i,256,3)
            _IR_INSERT_VECTOR_TYPE(i,512,3)


            _IR_INSERT_VECTOR_TYPE(i,8,4)
            _IR_INSERT_VECTOR_TYPE(i,16,4)
            _IR_INSERT_VECTOR_TYPE(i,32,4)
            _IR_INSERT_VECTOR_TYPE(i,64,4)
            _IR_INSERT_VECTOR_TYPE(i,128,4)
            _IR_INSERT_VECTOR_TYPE(i,256,4)
            _IR_INSERT_VECTOR_TYPE(i,512,4)


            _IR_INSERT_VECTOR_TYPE(f,32,2)
            _IR_INSERT_VECTOR_TYPE(f,64,2)
            _IR_INSERT_VECTOR_TYPE(f,128,2)


            _IR_INSERT_VECTOR_TYPE(f,32,3)
            _IR_INSERT_VECTOR_TYPE(f,64,3)
            _IR_INSERT_VECTOR_TYPE(f,128,3)


            _IR_INSERT_VECTOR_TYPE(f,32,4)
            _IR_INSERT_VECTOR_TYPE(f,64,4)
            _IR_INSERT_VECTOR_TYPE(f,128,4)

#define __XLINK(X,Y,Z) X##x##Y##x##Z

#define _IR_INSERT_MATRIX_TYPE(n,c,x,y,z) auto __ELINK(__XMERAGE(__XMERAGE(mat,n),c),__XLINK(x,y,z) ) = new MatrixType( x,y,z,ptr_##n##c );\
            m_typeMap.insert(std::make_pair("mat<"#n#c"," #x "x" #y "x"#z">", __ELINK(__XMERAGE(__XMERAGE(mat,n),c),__XLINK(x,y,z) )));

            _IR_INSERT_MATRIX_TYPE(i,8,2,2,1)
            _IR_INSERT_MATRIX_TYPE(i,16,2,2,1)
            _IR_INSERT_MATRIX_TYPE(i,32,2,2,1)
            _IR_INSERT_MATRIX_TYPE(i,64,2,2,1)
            _IR_INSERT_MATRIX_TYPE(i,128,2,2,1)
            _IR_INSERT_MATRIX_TYPE(i,256,2,2,1)
            _IR_INSERT_MATRIX_TYPE(i,512,2,2,1)

            _IR_INSERT_MATRIX_TYPE(i, 8, 2, 3, 1)
            _IR_INSERT_MATRIX_TYPE(i, 16, 2, 3, 1)
            _IR_INSERT_MATRIX_TYPE(i, 32, 2, 3, 1)
            _IR_INSERT_MATRIX_TYPE(i, 64, 2, 3, 1)
            _IR_INSERT_MATRIX_TYPE(i, 128, 2, 3, 1)
            _IR_INSERT_MATRIX_TYPE(i, 256, 2, 3, 1)
            _IR_INSERT_MATRIX_TYPE(i, 512, 2, 3, 1)

            _IR_INSERT_MATRIX_TYPE(i,8,2,4,1)
            _IR_INSERT_MATRIX_TYPE(i,16,2,4,1)
            _IR_INSERT_MATRIX_TYPE(i,32,2,4,1)
            _IR_INSERT_MATRIX_TYPE(i,64,2,4,1)
            _IR_INSERT_MATRIX_TYPE(i,128,2,4,1)
            _IR_INSERT_MATRIX_TYPE(i,256,2,4,1)
            _IR_INSERT_MATRIX_TYPE(i,512,2,4,1)

            _IR_INSERT_MATRIX_TYPE(i,8,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,16,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,32,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,64,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,128,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,256,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,512,3,2,1)

            _IR_INSERT_MATRIX_TYPE(i,8,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,16,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,32,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,64,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,128,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,256,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,512,3,3,1)

            _IR_INSERT_MATRIX_TYPE(i,8,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,16,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,32,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,64,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,128,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,256,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,512,3,4,1)

            _IR_INSERT_MATRIX_TYPE(i,8,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,16,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,32,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,64,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,128,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,256,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,512,4,2,1)


            _IR_INSERT_MATRIX_TYPE(i,8,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,16,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,32,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,64,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,128,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,256,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,512,4,3,1)

            _IR_INSERT_MATRIX_TYPE(i,8,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,16,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,32,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,64,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,128,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,256,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,512,4,4,1)

            

    }

}