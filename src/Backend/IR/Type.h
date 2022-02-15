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
        enum RC_TYPE {
            kRow,
            kCol,
        };
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
        RC_TYPE m_type;
    };
    
    class MatrixType : public Type{
    public:
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
        uint32_t getDimSize() const {
            return m_dimSize.size();
        }
        uint32_t atDim(uint32_t index) const {
            return m_dimSize.at( index );
        }
        Type* getType() const {
            return m_basicType;
        }
    private:
        std::vector<uint32_t> m_dimSize;
        Type* m_basicType;
    };

    class StructType : public Type {

    };
    class ClassType : public Type {

    };
    class EnumType : public Type {


    };
    class UnionType : public Type {

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
            return false;
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

    class TypeManger {
    public:
        TypeManger( ) 
            : m_boolType ( new BoolType() )
            , m_voidType( new VoidType() )
        {
            _InitIntegerType();
            _InitFloatType();
        }

        Type * getFloatType( uint32_t size) const{
            auto iter = m_floatTypeMap.find(size);
            if (iter == m_floatTypeMap.end()) {
                return nullptr;
            }
            return iter->second;
        }

        Type* getIntegerType(uint32_t size) const {
            auto iter = m_integerTypeMap.find(size);
            if (iter == m_integerTypeMap.end()) {
                return nullptr;
            }
            return iter->second;
        }
        Type* getVoidType() const {
            return m_voidType;
        }
        Type* getBoolType() const {
            return m_boolType;
        }

        Type* getVectorType(Type* type, size_t n)  const {
            return nullptr;
        }

        void AddVectorType(uint32_t size, Type* type) {
        
        }

        void AddMatrixType(uint32_t size, Type* type) {
        
        }

        void AddFunctionType(Type* ret, std::vector<Type*> param) {
        
        }

        void AddStructType( ){
        
        }
    private:
        void _InitIntegerType() {
            m_integerTypeMap.insert( std::make_pair(1, new IntegerType(1)) );
            m_integerTypeMap.insert( std::make_pair(2, new IntegerType(2)) );
            m_integerTypeMap.insert( std::make_pair(4, new IntegerType(4)) );
            m_integerTypeMap.insert( std::make_pair(8, new IntegerType(8)) );
            m_integerTypeMap.insert( std::make_pair(16, new IntegerType(16)) );
            m_integerTypeMap.insert( std::make_pair(32, new IntegerType(32)) );
            m_integerTypeMap.insert(std::make_pair(64, new IntegerType(64)) );
        }
        void _InitFloatType() {
            m_floatTypeMap.insert( std::make_pair(4, new IntegerType(4)) );
            m_floatTypeMap.insert( std::make_pair(8, new IntegerType(8)) );
            m_floatTypeMap.insert( std::make_pair(16, new IntegerType(16)) );
            m_floatTypeMap.insert( std::make_pair(32, new IntegerType(32)) );
            m_floatTypeMap.insert( std::make_pair(64, new IntegerType(64)) );
        }
    private:
        std::map<uint32_t, Type*> m_floatTypeMap;
        std::map<uint32_t, Type*> m_integerTypeMap;
        BoolType*       m_boolType;
        VoidType*       m_voidType;

    };


}