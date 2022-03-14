#pragma once
#include <stdint.h>
#include <string>
#include <vector>

#include "Backend/IR/Value.h"
#include "Backend/IR/Constant.h"
#include "ADT/plist.h"

namespace IR {

    enum class InstructionType : uint32_t {
        kControl    = 0, /// 控制指令
        kArithmetic = 1, /// 数学指令
        kMemory     = 2,
        kCast       = 3,
        kPseudo     = 4, /// 伪指令

        kUnknown    = 0xFFFFFFFF,
    };

    class BasicBlock;
    class IRContext;
    class Function;
    
    /// <summary>
    /// 在llvm之中,我们使用的Instruction继承与Value,在这里我分开了,因为一个代码的操作一个代表的数据
    /// </summary>
    class Instruction : public ADT::list_node<Instruction> {
    public:
        enum OpCode : uint32_t {
#define ENUM_IR_INSTRUCTION
#include "Backend/IR/IROpCode.inl"
#undef ENUM_IR_INSTRUCTION
        };
    public:
        Instruction(OpCode op)
            : m_Op(op)
            , m_BasicBlock(nullptr)
            , m_IRContext( nullptr )
            , m_Result( nullptr )
        {}

        void setBasicBlock(BasicBlock* block) {
            m_BasicBlock = block;
        }

        BasicBlock* getBasicBlock() {
            return m_BasicBlock;
        }

        const BasicBlock* getBasicBlock() const {
            return m_BasicBlock;
        }

        void release() {
            this->~Instruction();
        }

        bool isUnaryOp() const;
        bool isBinaryOp() const;
        bool isInsHaveResult() const {
            return isInsHaveResult(m_Op);
        }
        InstructionType getInsType() const;
        OpCode getOpCode() const {
            return m_Op;
        }
        char const* getOpStr()const {
            return getOpStr(m_Op);
        }
        Value* getRetValue() const {
            return m_Result;
        }

        static bool isUnaryOp(Instruction::OpCode op);
        static bool isBinaryOp(Instruction::OpCode op);
        static bool isInsHaveResult( Instruction::OpCode op);
        static InstructionType getInsType(IR::Instruction::OpCode Op);
        static const char* getOpStr(OpCode code);

        using OperandIterator = std::vector<Value*>::iterator;
        using constOperandIterator = std::vector<Value*>::const_iterator;
        
        OperandIterator operandBegin() {
            return m_Operands.begin();
        }
        
        OperandIterator operandEnd() {
            return m_Operands.end();
        }
        
        constOperandIterator operandBegin() const {
            return m_Operands.begin();
        }
        
        constOperandIterator operandEnd() const {
            return m_Operands.end();
        }
        
        size_t oprandSize() const {
            return m_Operands.size();
        }
        
        Value* operandAt(size_t index) {
            return m_Operands.at(index);
        }

        void addOperand(Value* operand) {
            m_Operands.push_back(operand);
        }

        Value* getResult() {
            return m_Result;
        }

        Value* getResult() const {
            return m_Result;
        }

  
    protected:
        virtual ~Instruction() {
            
        }

    protected:
        OpCode m_Op;
        BasicBlock* m_BasicBlock;
        IRContext*  m_IRContext;
        Function*   m_Function;
        std::vector<Value*> m_Operands;
        Value*              m_Result;
    };



    class ArithmeticIns : public Instruction {
    public:
        ArithmeticIns(Instruction::OpCode op, const char* name, Type const* type )
            : Instruction( op)
        {
            m_RetValue = new Value(name, type, static_cast<Instruction*>(this));
        }

        ArithmeticIns(Instruction::OpCode op, Value* retValue)
            : Instruction( op )
        {
            m_RetValue = retValue;
        }

    private:
        Value* m_RetValue;
    };
        
    /// <summary>
    class ErrorIns : public Instruction{
    public:
        explicit ErrorIns( ) 
            : Instruction( Instruction::OpCode::kError )
        {
        }
    private:
        OpCode m_readCode;
    };
    
    class UnaryOpIns : public ArithmeticIns{
    public:
        explicit UnaryOpIns(OpCode op, char const* name, Type const* type,Value* v) 
            : ArithmeticIns( op,  name, type )
            , m_FirstOperand( v )
        {
        
        }
        explicit UnaryOpIns(OpCode op, Type const* type,std::string const& name, Value * v) 
            : ArithmeticIns( op, name.c_str(), type)
            , m_FirstOperand( v)
        {
        
        }
        Value* getFirstOperand() const {
            return m_FirstOperand;
        }

    private:
        Value* m_FirstOperand;
    };

    /// 
    /// 二元算术指令 add mul  div 
    ///             mmul     vmul
    ///             pmuml    pvmul
    ///             
    class BinaryOpIns: public ArithmeticIns{
    public:
        BinaryOpIns(OpCode op,std::string const &name, Type const* type, Value* v1, Value* v2 ) 
            : ArithmeticIns( op, name.c_str() , type)
            , m_FirstOperand( v1 )
            , m_SecondOperand( v2 ) 
        {
            
        }
        BinaryOpIns(OpCode op,  const char* name, Type const* type,Value* v1, Value* v2 ) 
            : ArithmeticIns( op, name , type)
            , m_FirstOperand( v1 )
            , m_SecondOperand( v2 )
        {
        }
        Value* getFirstOperand() const {
            return m_FirstOperand;
        }

        Value* getSecondOperand() const {
            return m_SecondOperand;
        }

        Value* getSecondOperand() {
            return m_SecondOperand;
        }


        
    private:
        Value* m_FirstOperand;
        Value* m_SecondOperand;
    };
	
	class AllocIns : public Instruction{
	public:
        explicit AllocIns(char const* name, Type const* type) 
            : Instruction( OpCode::kAlloc )
            , m_RetValue( nullptr )
            , m_FirstOperand( nullptr )
        {
            m_RetValue = new Value(name, type, this);
        }
        explicit AllocIns(std::string const& name, Type const* type) 
            : Instruction( OpCode::kAlloc )
            , m_RetValue( nullptr )
            , m_FirstOperand( nullptr )
        {
            m_RetValue = new Value(name.c_str( ), type, this);
        }
		explicit AllocIns(char const* name, const Type* type, Value* value )
			: Instruction(OpCode::kAlloc )
            , m_RetValue( nullptr )
            , m_FirstOperand( value )
		{
            m_RetValue = new Value(name, type, this);
		}

        explicit AllocIns(char const* name, Type const* type, Constant * cv) 
            : Instruction( OpCode::kAlloc )
            , m_RetValue( nullptr )
            , m_FirstOperand( cv )
        {
            m_RetValue = new Value(name, type, this);
        }

        explicit AllocIns(std::string const& name, Type const* type, Constant* cv)
            : Instruction( OpCode::kAlloc )
            , m_RetValue( nullptr )
            , m_FirstOperand( cv )
        {
            m_RetValue = new Value(name.c_str( ), type, this);
        }

        explicit AllocIns(std::string const& name, Type const* type, Value* value) 
            : Instruction( OpCode::kAlloc )
            , m_RetValue( nullptr )
            , m_FirstOperand( value )
        {
            m_RetValue = new Value(name.c_str(), type, this);
        }


        Value* getFirstOperand() const {
            return m_FirstOperand;
        }

    private:
        Value* m_RetValue;
        Value* m_FirstOperand;
	};
   
    class AssignIns : public Instruction {
    public:
        explicit AssignIns(Value* ret, Value* v) 
            : Instruction( OpCode::kAssign )
            , m_RetValue( ret )
            , m_FirstOperand( v )
        {
        }

        Value* getFirstOperand() const {
            return m_FirstOperand;
        }
    private:
        Value* m_RetValue;
        Value* m_FirstOperand;
    };


    /// Label 也是一条指令
    class Label : public Instruction , public Value {
    public:
        explicit Label(std::string const& label)
            :Value( label.c_str(), nullptr, this )
            ,Instruction( IR::Instruction::OpCode::kLabel )
            , m_label( label )
        {
            
        }
        
        
        std::string getLabelName() const {
            return m_label;
        }

        bool isLocalLabel() const {
            return m_bLocal;
        }
    public:
        const std::string& getLabelStr() const {
            return m_label;
        }
    private:
        std::string m_label;
        uint32_t    m_bLocal : 1;
    };

    class Jmp : public Instruction {
    public:
        explicit Jmp(std::string const& label)
            : Instruction( IR::Instruction::OpCode::kJmp )
            , m_label( label )
        {
        }

        const std::string& getJmpLabel() const {
            return m_label;
        }
    private:
        std::string m_label;
    };

    class Br : public Instruction {
    public:
        explicit Br( Value* value,
                     std::string const& trueLabel ,
                     std::string const& falseLabel)
            : Instruction( IR::Instruction::OpCode::kBr )
            , m_value( value )
            , m_trueLabel( trueLabel)
            , m_falseLabel( falseLabel )
        {
        }

        std::string const& getTrueLabel() const {
            return m_trueLabel;
        }

        std::string const& getFalseLabel() const {
            return m_falseLabel;
        }
        Value* getCmpValue() const {
            return m_value;
        }
        
    private:
        Value* m_value;
        std::string m_trueLabel;
        std::string m_falseLabel;
    };

    
    class Ret : public Instruction {
    public:
        explicit Ret() 
            : Instruction( IR::Instruction::OpCode::kRet)
            , m_value( nullptr )
        {}
        explicit Ret(Value* value) 
            : Instruction( IR::Instruction::OpCode::kRet )
            , m_value( value )
        {}

        Value* getInsRetValue() const{
            return m_value;
        }
    private:
        Value* m_value;
    };

}