#pragma once
#include <map>
#include <vector>
#include "Backend/IR/Instruction.h"
namespace IR {
    /// 只能支持基础数据类型和简单复合数据类型
    /// type系统是很重要的
    class Type {
    public:
        virtual bool isVoidType( ) const = 0;
        virtual bool isBoolType( ) const = 0;
        virtual bool isIntegerType( ) const = 0;
        virtual bool isFloatType( ) const = 0;
        virtual bool isVectorType( ) const = 0;
        virtual bool isMatrixType( ) const = 0;
        virtual Type const* isSupportOp(Instruction::OpCode) const = 0;
    };

    class VoidType : public Type {
    public:
        bool isVoidType() const  override {
            return true;
        }
        bool isBoolType() const override {
            return false;
        }
        bool isIntegerType() const override {
            return false;
        }
        bool isFloatType() const override {
            return false;
        }
        bool isVectorType() const override {
            return false;
        }
        bool isMatrixType() const override {
            return false;
        }
        Type const* isSupportOp(Instruction::OpCode) const override;
    };

    class BoolType : public Type {
    public:
        bool isVoidType() const override {
            return false;
        }
        bool isBoolType() const override {
            return true;
        }
        bool isIntegerType( ) const override {
            return false;
        }
        bool isFloatType() const override {
            return false;
        }
        bool isVectorType() const override {
            return false;
        }
        bool isMatrixType() const override {
            return false;
        }
        Type const* isSupportOp(Instruction::OpCode)  const override;
    };

    class IntegerType : public Type {
    public:
        IntegerType(uint32_t size) 
            : m_size( size )
        {}
        bool isVoidType() const override {
            return false;
        }
        bool isBoolType() const override {
            return false;
        }
        bool isIntegerType() const override {
            return true;
        }
        bool isFloatType() const override {
            return false;
        }
        bool isVectorType() const override {
            return false;
        }
        bool isMatrixType() const override {
            return false;
        }
        Type const* isSupportOp(Instruction::OpCode)  const override;
    public:
        uint32_t getSize() const {
            return m_size;
        }
        
    private:
        uint32_t m_size;
        
    };

    class FloatType : public Type{
    public:
        FloatType( uint32_t size) 
            : m_size(size) 
        {}
        bool isVoidType() const override {
            return false;
        }
        bool isBoolType() const override {
            return false;
        }
        bool isIntegerType() const override {
            return false;
        }
        bool isFloatType() const override {
            return true;
        }
        bool isVectorType() const override {
            return false;
        }
        bool isMatrixType() const override {
            return false;
        }
        Type const* isSupportOp(Instruction::OpCode)  const override;

    public:
        uint32_t getSize() const {
            return m_size;
        }
    private:
        uint32_t m_size;
    };

    class VectorType : public Type{
    public:
        VectorType(uint32_t dimSize, Type* baseType)
            : m_dimSize( dimSize )
            , m_basicType( baseType )
        {
        }
        bool isVoidType() const override {
            return false;
        }
        bool isBoolType() const override {
            return false;
        }
        bool isIntegerType() const override {
            return false;
        }
        bool isFloatType() const override {
            return true;
        }
        bool isVectorType() const override {
            return true;
        }
        bool isMatrixType() const override {
            return false;
        }
        Type const* isSupportOp(Instruction::OpCode)  const override;
    public:

        uint32_t getDimSize() const {
            return m_dimSize;
        }
        const Type* getBasicType() const {
            return m_basicType;
        }

    private:
        
        uint32_t m_dimSize;
        Type* m_basicType;
    };
    
    class MatrixType : public Type{
    public:
        MatrixType(uint32_t x, uint32_t y,uint32_t z, Type* baseType ) 
            : m_dimSizeX( x)
            , m_dimSizeY( y)
            , m_dimSizeZ( z)
            , m_basicType ( baseType)
        {}
        bool isVoidType() const override {
            return false;
        }
        bool isMatrixType() const override {
            return true;
        }
        bool isBoolType() const override {
            return false;
        }
        bool isIntegerType() const override {
            return false;
        }
        bool isFloatType() const override {
            return true;
        }
        bool isVectorType() const override {
            return false;
        }
        bool isMatrixType() const override {
            return true;
        }
        Type const* isSupportOp(Instruction::OpCode)  const override;
    public:
        Type* getType() const {
            return m_basicType;
        }
    private:
        uint32_t m_dimSizeX;
        uint32_t m_dimSizeY;
        uint32_t m_dimSizeZ;
        Type* m_basicType;
    };


    class FunctionType : public Type {
    public:
        bool isVoidType() const override {
            return false;
        }
        bool isBoolType() const override {
            return false;
        }
        bool isIntegerType() const override {
            return false;
        }
        bool isFloatType() const override {
            return false;
        }
        bool isVectorType() const override {
            return false;
        }
        bool isMatrixType() const override {
            return false;
        }
        Type const* isSupportOp(Instruction::OpCode)  const override {
            return nullptr;
        }

    public:
        FunctionType( Type* retType );
        void addParamType(  Type* type );
        Type* getReturnType() const;
        size_t sizeParamsType() const;
        Type* atParamType(uint32_t i) const;
    private:
        Type* m_retType;
        std::vector<Type*> m_paramsType;
    };
    /*
     * 容器类,支持当前Context之中所有的类型
     */
    class TypeManger {
    public:
        TypeManger( ) 
            : m_boolType ( new BoolType() )
            , m_voidType( new VoidType() )
        {
            _InitBasicType();
        }

        Type* getVoidType() const {
            return m_voidType;
        }
        Type* getBoolType() const {
            return m_boolType;
        }

        Type* getTypeFromName(std::string_view const& name) const {
            std::string strName(name);
            auto iter = m_typeMap.find(strName);
            if (iter != m_typeMap.end()) {
                return iter->second;
            }
            return nullptr;
        }


    private:
        void _InitBasicType() {
            
            m_typeMap.insert(std::make_pair( "bool", m_boolType));
            m_typeMap.insert(std::make_pair( "void", m_voidType));
            
            _InitType();

        }
        void _InitType() {
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
#define _IR_INSERT_VECTOR_TYPE(n,y,x) auto __LINK(__XMERAGE(__XMERAGE(vec,n),y),x) = new VectorType( x,ptr_##n##y );\
            m_typeMap.insert(std::make_pair("vec<"#n#y","#x">", __LINK(__XMERAGE(__XMERAGE(vec,n),y),x) ));


                _IR_INSERT_VECTOR_TYPE(i,8,2)
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
            m_typeMap.insert(std::make_pair("vec<"#n#c"," #x "x" #y "x"#z">", __ELINK(__XMERAGE(__XMERAGE(mat,n),c),__XLINK(x,y,z) )));
            
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
            _IR_INSERT_MATRIX_TYPE(i,8,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,2,1)

            _IR_INSERT_MATRIX_TYPE(i,8,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,3,1)

            _IR_INSERT_MATRIX_TYPE(i,8,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,3,4,1)

            _IR_INSERT_MATRIX_TYPE(i,8,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,2,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,2,1)
            
                    
            _IR_INSERT_MATRIX_TYPE(i,8,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,3,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,3,1)

            _IR_INSERT_MATRIX_TYPE(i,8,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,4,1)
            _IR_INSERT_MATRIX_TYPE(i,8,4,4,1)



        }
    private:
        BoolType*       m_boolType;
        VoidType*       m_voidType;
        std::map<std::string, Type*> m_typeMap;

    };


}
