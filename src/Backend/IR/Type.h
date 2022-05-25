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

        Type* getTypeFromName(std::string_view const& name) const {
            std::string strName(name);
            auto iter = m_typeMap.find(strName);
            if (iter != m_typeMap.end()) {
                return iter->second;
            }
            return nullptr;
        }

        Type* getTypeFromName(std::string const& name) const {
            return nullptr;
        }

        Type* getTypeFromName(const char* name) const {
            return nullptr;
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
        void _InitBasicType() {
            _InitIntegerType();
            _InitFloatType();
            
            m_typeMap.insert(std::make_pair( "bool", m_boolType));
            m_typeMap.insert(std::make_pair( "void", m_voidType));


        }
        void _InitIntegerType() {
#define __IR_INSERT_INTEGER_TYPE(x)\
            auto ptr_##x = new IntegerType( x );\
            m_integerTypeMap.insert(std::make_pair(x, ptr_##x));\
            m_typeMap.insert(std::make_pair("i"#x, ptr_##x ));

            __IR_INSERT_INTEGER_TYPE(1)
            __IR_INSERT_INTEGER_TYPE(8)
            __IR_INSERT_INTEGER_TYPE(16)
            __IR_INSERT_INTEGER_TYPE(32)
            __IR_INSERT_INTEGER_TYPE(64)
            __IR_INSERT_INTEGER_TYPE(128)
            __IR_INSERT_INTEGER_TYPE(256)
            __IR_INSERT_INTEGER_TYPE(512)
            __IR_INSERT_INTEGER_TYPE(1024)
            __IR_INSERT_INTEGER_TYPE(2048)
            __IR_INSERT_INTEGER_TYPE(4096)
#undef __INSERT_INTEGER_TYPE

        }
        void _InitFloatType() {
#define __IR_INSERT_FLOAT_TYPE(x)\
            auto ptr_##x = new FloatType( x );\
            m_floatTypeMap.insert(std::make_pair(x, ptr_##x));\
            m_typeMap.insert(std::make_pair("f"#x, ptr_##x ));

                __IR_INSERT_FLOAT_TYPE(32)
                __IR_INSERT_FLOAT_TYPE(64)
                __IR_INSERT_FLOAT_TYPE(128)
                __IR_INSERT_FLOAT_TYPE(256)
                __IR_INSERT_FLOAT_TYPE(512)
                __IR_INSERT_FLOAT_TYPE(1024)
                __IR_INSERT_FLOAT_TYPE(2048)
                __IR_INSERT_FLOAT_TYPE(4096)
#undef __INSERT_INTEGER_TYPE
        }
    private:
        std::map<uint32_t, Type*> m_floatTypeMap;
        std::map<uint32_t, Type*> m_integerTypeMap;
        BoolType*       m_boolType;
        VoidType*       m_voidType;
        std::map<std::string, Type*> m_typeMap;

    };


}
