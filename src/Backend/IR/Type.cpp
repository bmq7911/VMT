#include "Backend/IR/Instruction.h"
#include "Backend/IR/Function.h"
#include "Backend/IR/Type.h"
#include "utils/utils.h"
#include "Backend/IR/IRContext.h"

namespace IR {
    //
}

namespace IR {


}

namespace IR {

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
            Instruction::OpCode::kEqual,
            Instruction::OpCode::kNotEqual,
            Instruction::OpCode::kLess,
            Instruction::OpCode::kLessEqual,
            Instruction::OpCode::kGreater,
            Instruction::OpCode::kGreaterEqual,
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
    

        TypeParse::TypeParse(std::string_view const& name) 
            : m_src( name )
        {}

        Type* TypeParse::parse( TypeManger * manger) {
            std::string_view ss;
            std::string name;
            std::string typeName;

            Token tok = _scan( ss );
            if (tok == TypeParse::Token::kVEC) {
                name += "vec";
                tok = _scan(ss);
                if (tok != TypeParse::Token::kLAB)
                    return nullptr;
                name += "<";
                tok = _scan(ss);
                if (tok != TypeParse::Token::kTYPE)
                    return nullptr;

                typeName = std::string(ss.data(),ss.length() );
                name += std::string( ss.data(), ss.length());

                tok = _scan(ss);
                if (tok != TypeParse::Token::kComma)
                    return nullptr;
                name += ",";
                
                tok = _scan(ss);
                
                uint32_t row = 1;
                uint32_t col = 1;

                if (tok != TypeParse::Token::kNUM)
                    return nullptr;
                row = std::atoi(ss.data());
                name += std::string(ss.data(), ss.length());

                tok = _scan(ss);

                if (tok == TypeParse::Token::kRAB) {
                    if (row <= 1) {
                        return nullptr;
                    }
                    else {
                        tok = _scan(ss);
                        name += ",1>";
                        if (tok != kEOF)
                            return nullptr;
                        else { /// 生成新的数据类型
                            auto type = manger->getTypeFromName( typeName);
                            if (nullptr == type) {
                                return nullptr;
                            }
                            else {
                                return manger->addType<VectorType>(typeName, row, col, type);
                            }
                        }
                    }
                }
                else if( tok == TypeParse::Token::kComma) {
                    if (row != 1) {
                        return nullptr;
                    }
                    else {
                        tok = _scan(ss);
                        if (tok != TypeParse::Token::kNUM)
                            return nullptr;
                        name += ",";
                        name += std::string(ss.data(), ss.length());
                        
                        tok = _scan(ss);
                        if (tok != TypeParse::Token::kRAB)
                            return nullptr;
                        name += ">";

                        tok = _scan(ss);
                        if (tok != TypeParse::Token::kEOF)
                            return nullptr;
                        else {
                            auto type = manger->getTypeFromName(typeName);
                            if (nullptr == type) {
                                return nullptr;
                            }
                            else {
                                return manger->addType<VectorType>( typeName, row,col, type);
                            }
                        }
                    }
                }
                else {
                    return nullptr;
                }
            }
            else if (tok == TypeParse::Token::kMAT) {
                name += "mat";
                tok = _scan(ss);
                if (tok != TypeParse::Token::kLAB)
                    return nullptr;
                name += "<";
                tok = _scan(ss);
                if (tok != TypeParse::Token::kTYPE)
                    return nullptr;

                typeName = std::string(ss.data(), ss.length());
                name += std::string(ss.data(), ss.length());

                tok = _scan(ss);
                if (tok != TypeParse::Token::kComma)
                    return nullptr;
                name += ",";

                tok = _scan(ss);

                uint32_t row = 1;
                uint32_t col = 1;

                if (tok != TypeParse::Token::kNUM)
                    return nullptr;
                row = std::atoi(ss.data());
                name += std::string(ss.data(), ss.length());

                tok = _scan(ss);
                if (tok != TypeParse::Token::kComma)
                    return nullptr;
                name += ",";

                tok = _scan(ss);
                if (tok != TypeParse::Token::kNUM)
                    return nullptr;
                col = std::atoi(ss.data());
                name += std::string( ss.data(), ss.length());
                
                if (tok != TypeParse::Token::kRAB)
                    return nullptr;
                else {
                    auto type = manger->getTypeFromName(typeName);
                    if (nullptr == type) {
                        return nullptr;
                    }
                    else {
                        return manger->addType<MatrixType>(typeName, row, col, type);
                    }
                    return nullptr;
                }
            }
            else {
                return nullptr;
            }
        }
        TypeParse::Token TypeParse::_scan(std::string_view& value) {
            m_index++;
            if (m_index == m_src.length()) {
                return kEOF;
            }
            while (' ' == m_src[m_index]) {
                m_index++;
            }
            char ch = m_src[m_index];
            if (std::isalpha(ch)) {
                uint32_t startIndex = m_index;
                while ( std::isalnum(ch) && m_index < m_src.length()) {
                    m_index++;
                    ch = m_src[m_index];
                }
                m_index--;
                std::string_view ss(m_src.data() + startIndex, m_index - startIndex + 1);
                value = ss;
                if (ss == "vec") {
                    return TypeParse::Token::kVEC;
                }
                else if (ss == "mat") {
                    return TypeParse::Token::kMAT;
                }
                else {
                    return TypeParse::Token::kTYPE;
                }
            }
            else if ('0' <= ch && ch <= '9') {
                uint32_t startIndex = m_index;
                while ( ('0' <= ch && ch <= '9') && m_index < m_src.length()) {
                    m_index++;
                    ch = m_src[m_index];
                }
                m_index--;
                std::string_view ss(m_src.data() + startIndex, m_index - startIndex + 1);
                value = ss;
                return TypeParse::Token::kNUM;
            }
            else if (',' == ch) {
                return TypeParse::Token::kComma;
            }
            else if ('<' == ch) {
                return TypeParse::Token::kLAB;
            }
            else if ('>' == ch) {
                return TypeParse::Token::kRAB;
            }
            else {
                return TypeParse::Token::kERROR;
            }
        
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

#define _IR_INSERT_VECTOR_TYPE(n,y,x) IR::VectorType* __ELINK(__XMERAGE(__XMERAGE(vec,n),y),x) = new IR::VectorType( x,1,ptr_##n##y );\
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

#define __XLINK(X,Y) X##x##Y

#define _IR_INSERT_MATRIX_TYPE(n,c,x,y) auto __ELINK(__XMERAGE(__XMERAGE(mat,n),c),__XLINK(x,y) ) = new MatrixType( x,y,ptr_##n##c );\
            m_typeMap.insert(std::make_pair("mat<"#n#c"," #x "x" #y">", __ELINK(__XMERAGE(__XMERAGE(mat,n),c),__XLINK(x,y) )));

            _IR_INSERT_MATRIX_TYPE(i,8,2,2)
            _IR_INSERT_MATRIX_TYPE(i,16,2,2)
            _IR_INSERT_MATRIX_TYPE(i,32,2,2)
            _IR_INSERT_MATRIX_TYPE(i,64,2,2)
            _IR_INSERT_MATRIX_TYPE(i,128,2,2)
            _IR_INSERT_MATRIX_TYPE(i,256,2,2)
            _IR_INSERT_MATRIX_TYPE(i,512,2,2)

            _IR_INSERT_MATRIX_TYPE(i, 8, 2, 3)
            _IR_INSERT_MATRIX_TYPE(i, 16, 2, 3)
            _IR_INSERT_MATRIX_TYPE(i, 32, 2, 3)
            _IR_INSERT_MATRIX_TYPE(i, 64, 2, 3)
            _IR_INSERT_MATRIX_TYPE(i, 128, 2, 3)
            _IR_INSERT_MATRIX_TYPE(i, 256, 2, 3)
            _IR_INSERT_MATRIX_TYPE(i, 512, 2, 3)

            _IR_INSERT_MATRIX_TYPE(i,8,2,4)
            _IR_INSERT_MATRIX_TYPE(i,16,2,4)
            _IR_INSERT_MATRIX_TYPE(i,32,2,4)
            _IR_INSERT_MATRIX_TYPE(i,64,2,4)
            _IR_INSERT_MATRIX_TYPE(i,128,2,4)
            _IR_INSERT_MATRIX_TYPE(i,256,2,4)
            _IR_INSERT_MATRIX_TYPE(i,512,2,4)

            _IR_INSERT_MATRIX_TYPE(i,8,3,2)
            _IR_INSERT_MATRIX_TYPE(i,16,3,2)
            _IR_INSERT_MATRIX_TYPE(i,32,3,2)
            _IR_INSERT_MATRIX_TYPE(i,64,3,2)
            _IR_INSERT_MATRIX_TYPE(i,128,3,2)
            _IR_INSERT_MATRIX_TYPE(i,256,3,2)
            _IR_INSERT_MATRIX_TYPE(i,512,3,2)

            _IR_INSERT_MATRIX_TYPE(i,8,3,3)
            _IR_INSERT_MATRIX_TYPE(i,16,3,3)
            _IR_INSERT_MATRIX_TYPE(i,32,3,3)
            _IR_INSERT_MATRIX_TYPE(i,64,3,3)
            _IR_INSERT_MATRIX_TYPE(i,128,3,3)
            _IR_INSERT_MATRIX_TYPE(i,256,3,3)
            _IR_INSERT_MATRIX_TYPE(i,512,3,3)

            _IR_INSERT_MATRIX_TYPE(i,8,3,4)
            _IR_INSERT_MATRIX_TYPE(i,16,3,4)
            _IR_INSERT_MATRIX_TYPE(i,32,3,4)
            _IR_INSERT_MATRIX_TYPE(i,64,3,4)
            _IR_INSERT_MATRIX_TYPE(i,128,3,4)
            _IR_INSERT_MATRIX_TYPE(i,256,3,4)
            _IR_INSERT_MATRIX_TYPE(i,512,3,4)

            _IR_INSERT_MATRIX_TYPE(i,8,4,2)
            _IR_INSERT_MATRIX_TYPE(i,16,4,2)
            _IR_INSERT_MATRIX_TYPE(i,32,4,2)
            _IR_INSERT_MATRIX_TYPE(i,64,4,2)
            _IR_INSERT_MATRIX_TYPE(i,128,4,2)
            _IR_INSERT_MATRIX_TYPE(i,256,4,2)
            _IR_INSERT_MATRIX_TYPE(i,512,4,2)


            _IR_INSERT_MATRIX_TYPE(i,8,4,3)
            _IR_INSERT_MATRIX_TYPE(i,16,4,3)
            _IR_INSERT_MATRIX_TYPE(i,32,4,3)
            _IR_INSERT_MATRIX_TYPE(i,64,4,3)
            _IR_INSERT_MATRIX_TYPE(i,128,4,3)
            _IR_INSERT_MATRIX_TYPE(i,256,4,3)
            _IR_INSERT_MATRIX_TYPE(i,512,4,3)

            _IR_INSERT_MATRIX_TYPE(i,8,4,4)
            _IR_INSERT_MATRIX_TYPE(i,16,4,4)
            _IR_INSERT_MATRIX_TYPE(i,32,4,4)
            _IR_INSERT_MATRIX_TYPE(i,64,4,4)
            _IR_INSERT_MATRIX_TYPE(i,128,4,4)
            _IR_INSERT_MATRIX_TYPE(i,256,4,4)
            _IR_INSERT_MATRIX_TYPE(i,512,4,4)

            

    }

}


namespace IR {
    
    Type* TypeChecker::checkOp(IR::IRContext& context, IR::Instruction::OpCode op, IR::Value* v1, IR::Value* v2) {
        /// <summary>
        /// 复杂数据类型
        /// </summary>
        if (v1->getType() != v2->getType()) {
            if (v1->getType()->isMatrixType() && v1->getType()->isVectorType()) {
                
            }
        }
        else {
            
        }
    }

    Type* TypeChecker::checkOp(IR::IRContext& context, IR::Instruction::OpCode op, IR::Value* v) {
    
    }

    Type* TypeChecker::_CheckIntegerBinaryOp(IR::IRContext& context,IR::Type* type, IR::Instruction::OpCode op) {

        static const Instruction::OpCode supportOp[] = {
            Instruction::OpCode::kAdd,
            Instruction::OpCode::kMinus,
            Instruction::OpCode::kMul,
            Instruction::OpCode::kDiv,
            Instruction::OpCode::kMod,
        };

        for (size_t i = 0; i < utils::array_size(supportOp); ++i) {
            if (supportOp[i] == op)
                return type;
        }

        static const Instruction::OpCode boolSupportOp[] = {
            Instruction::OpCode::kEqual,
            Instruction::OpCode::kNotEqual,
            Instruction::OpCode::kLess,
            Instruction::OpCode::kLessEqual,
            Instruction::OpCode::kGreater,
            Instruction::OpCode::kGreaterEqual,
        };

        for (size_t i = 0; i < utils::array_size(boolSupportOp); ++i) {
            if (boolSupportOp[i] == op)
                return context.getTypeManger().getBoolType( );
        }
        return nullptr;
    }
    
    Type* TypeChecker::_CheckIntegerUnaryOp(IR::IRContext& context,IR::Type * type, IR::Instruction::OpCode op) {
        static const Instruction::OpCode supportOp[] = {
            Instruction::OpCode::kMinus,
        };

        for (size_t i = 0; i < utils::array_size(supportOp); ++i) {
            if (supportOp[i] == op)
                return type;
        }
        static const Instruction::OpCode boolSupportOp[] = {
            Instruction::OpCode::kNot,
        };
        for (size_t i = 0; i < utils::array_size(boolSupportOp); ++i) {
            if (boolSupportOp[i] == op)
                return context.getTypeManger().getBoolType( );
        }
        return nullptr;
    }
    
    Type* TypeChecker::_CheckRealBinaryOp(IR::IRContext& context, IR::Type* type, IR::Instruction::OpCode op) {
        static const Instruction::OpCode supportOp[] = {
            Instruction::OpCode::kMinus,
            Instruction::OpCode::kSin,
            Instruction::OpCode::kCos,
            Instruction::OpCode::kTan,
            Instruction::OpCode::kAdd,
            Instruction::OpCode::kMul,
            Instruction::OpCode::kDiv,
        };

        for (size_t i = 0; i < utils::array_size(supportOp); ++i) {
            if (supportOp[i] == op)
                return type;
        }

        static const Instruction::OpCode boolSupportOp[] = {
            Instruction::OpCode::kEqual,
            Instruction::OpCode::kNotEqual,
            Instruction::OpCode::kLess,
            Instruction::OpCode::kLessEqual,
            Instruction::OpCode::kGreater,
            Instruction::OpCode::kGreaterEqual,
        };
        for (size_t i = 0; i < utils::array_size(boolSupportOp); ++i) {
            if (boolSupportOp[i] == op)
                return context.getTypeManger().getBoolType( );
        }
        return nullptr;
    }

    Type* TypeChecker::_CheckRealUnaryOp(IR::IRContext& context, IR::Type* type, IR::Instruction::OpCode op) {
        static const Instruction::OpCode supportOp[] = {
            Instruction::OpCode::kMinus,
        };

        for (size_t i = 0; i < utils::array_size(supportOp); ++i) {
            if (supportOp[i] == op)
                return type;
        }
        return nullptr;
    }

}