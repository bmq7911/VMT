#pragma once
#include <map>
#include <vector>
#include "Backend/IR/Instruction.h"

namespace {
    bool begin_with(std::string_view const& str, std::string_view const& with) {
        if (with.size() >= str.size()) {
            
        }
    }

}

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
            else {
                
            }
            return nullptr;
        }


    private:
        void _InitBasicType() {
            
            m_typeMap.insert(std::make_pair( "bool", m_boolType));
            m_typeMap.insert(std::make_pair( "void", m_voidType));
            
            _InitType();

        }
        void _InitType();
    private:
        BoolType*       m_boolType;
        VoidType*       m_voidType;
        std::map<std::string, Type*> m_typeMap;

    };


}
