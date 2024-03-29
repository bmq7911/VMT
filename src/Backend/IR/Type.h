#pragma once
#include <map>
#include <vector>
#include "Backend/IR/Instruction.h"

namespace {
    bool begin_with(std::string_view const& str, std::string_view const& with) {
        if (with.size() > str.size()) {
            return false;
        }
        else {
            for (size_t i = 0; i < with.length(); ++i) {
                if (str[i] != with[i])
                    return false;
            }
            return true;
        }
    }

}

namespace IR {
    class IRContext;

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
    };

    class IntegerType : public Type {
    public:
        IntegerType(uint32_t size) 
            : m_size( size )
            , m_isSigned( false )
        {}
        IntegerType(uint32_t size, bool isSigned) 
            : m_size( size )
            , m_isSigned( isSigned )
        {
        }

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
    public:
        uint32_t getSize() const {
            return m_size;
        }

    private:
        uint32_t m_size;
        uint32_t m_isSigned : 1;
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

    public:
        uint32_t getSize() const {
            return m_size;
        }
    private:
        uint32_t m_size;
    };

    class VectorType : public Type{
    public:
        VectorType(uint32_t rowSize, uint32_t colSize,  Type* baseType)
            : m_rowSize( rowSize )
            , m_colSize( colSize )
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
    public:

        uint32_t getRowSize() const {
            return m_rowSize;
        }
        uint32_t getColSize() const {
            return m_colSize;
        }
        const Type* getBasicType() const {
            return m_basicType;
        }

    private:
        uint32_t m_rowSize;
        uint32_t m_colSize;
        Type* m_basicType;
    };
    
    class MatrixType : public Type{
    public:
        MatrixType(uint32_t x, uint32_t y, Type* baseType ) 
            : m_dimSizeX( x)
            , m_dimSizeY( y)
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
    public:
        Type* getType() const {
            return m_basicType;
        }
    private:
        uint32_t m_dimSizeX;
        uint32_t m_dimSizeY;
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
   
    class StructType : public Type {
    public:
        struct Member {
            std::string memberName;
            Type* type;
        };
        
    private:
        std::string         m_typeName;
        std::vector<Member> m_members;
    };

    class TypeManger;
    class TypeParse {
    enum Token {
            kVEC,
            kMAT,
            kTYPE,
            kComma,
            kLAB,
            kRAB,
            kNUM,
            kEOF,
            kERROR,
        };
    public:
        TypeParse(std::string_view const& name);
        Type* parse( TypeManger * typeManger);
    private:
        Token _scan(std::string_view& value);
    private:
        
        uint32_t m_index{ uint32_t(-1) };
        std::string_view m_src;
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
        template<typename T,typename ... _Args>
        Type *addType( std::string const& name, _Args && ... args ) {
            auto type = new T( std::forward<_Args>(args) ...);
            m_typeMap.insert(std::make_pair(name, type));
            return type;
        }

        Type* getTypeFromName(std::string_view const& name) {
            std::string strName(name);
            auto iter = m_typeMap.find(strName);
            if (iter != m_typeMap.end()) {
                return iter->second;
            }
            else {
                TypeParse parse(name);
                return parse.parse( this );
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


    class TypeChecker {
    public:
        static const Type* checkOp( IR::IRContext & context, IR::Instruction::OpCode op,  IR::Value* v1, IR::Value * v2  );
        static const Type* checkOp(IR::IRContext& context, IR::Instruction::OpCode op, IR::Value* v);
    private:
        static const Type* _CheckIntegerBinaryOp(IR::IRContext& context,IR::Type const * type, IR::Instruction::OpCode);
        static const Type* _CheckIntegerUnaryOp(IR::IRContext& context, IR::Type const * type, IR::Instruction::OpCode);
        static const Type* _CheckRealBinaryOp(IR::IRContext& context, IR::Type const * type, IR::Instruction::OpCode);
        static const Type* _CheckRealUnaryOp(IR::IRContext& context, IR::Type const* type, IR::Instruction::OpCode);
        static const Type* _CheckBoolBinaryOp(IR::IRContext& context, IR::Type const * type, IR::Instruction::OpCode);
        static const Type* _CheckBoolUnaryOp(IR::IRContext& context, IR::Type const* type, IR::Instruction::OpCode);
    };

}
