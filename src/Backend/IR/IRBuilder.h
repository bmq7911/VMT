#pragma once
#include "Backend/IR/Value.h"
#include "Backend/IR/Instruction.h"
#include "Backend/IR/InsAllocoter.h"
#include "Backend/IR/IRContext.h"
#include "Backend/IR/Constant.h"
#include "Backend/IR/Function.h"
#include "Backend/IR/Type.h"

namespace IR {
    
    /// 1.通过脚本系统来实现
    /// 2.优化的主要目的是什么,就是在不影响结果的前提下减少指令的冗余
    /// 我们先不考虑IRBuilder
    /// 
    class IRBuilder {
    public:
        IRBuilder(std::shared_ptr<IR::IRContext>& context);
        ~IRBuilder();

    public:

        Constant* createConstant(Type const* type, float value);
        Constant* createConstant(Type const* type, double value);
        //Value* emitAlloc( Type const* type);
        //Value* emitLoad( Value *  );
        //Value* emitLoad(float value);
        //Value* emitLoad(double value);
        template<typename ... _Args>
        Value* emitPhi(_Args && ... args) {
            IR::Phi * phi = new IR::Phi( std::forward<_Args>( args) ... );
            return phi->getRetValue();
        }
        Value* emitBinaryOpIns(IR::Instruction::OpCode op, Value* v1, Value* v2);
        Value* emitUnaryOpIns(IR::Instruction::OpCode op, Value* v);
        Value* emitAlloc(const Type* type, const char* name);
        Value* emitAssign(Value* src, Value* dst);
        Br* emitBr(Value* v, const char* trueLabel, const char* falseLabel);
        Br* emitBr(Value* v, std::string const& trueLabel, std::string const& falseLabel);
        Jmp* emitJmp(const char* label);
        Jmp* emitJmp(std::string const& label);
        Ret* emitRet( Value *v);
        Label* emitLabel(std::string const& label);
        Label* emitLabel(const char* label);
        Value* emitSin(Value* v);
        Value* emitCos(Value* v);
        Value* emitTan(Value* v);
        Value* emitAdd(Value* v1, Value* v2);
        void emitAdd(Value* v1, Value* v2, Value* result);
        Value* emitMinus(Value* v1, Value* v2);
        Value* emitMul(Value* v1, Value* v2);
        Value* emitDiv(Value* v1, Value* v2);
        Value* emitMod(Value* v1, Value* v2);
        Value* emitAnd(Value* v1, Value* v2);
        Value* emitOr(Value* v1, Value* v2);
        Value* emitBitAnd(Value* v1, Value* v2);
        Value* emitBitOr(Value* v1, Value* v2);
        Value* emitBitXor(Value* v1, Value* v2);
        Value* emitDot(Value* v1, Value* v2);
        Value* emitCross(Value* v1, Value* v2);
        Value* emitTransposiont(Value* v);
        Value* emitInvert(Value* v);
        Function* emitFunction(const char* name, FunctionType* type);
    private:
        template<typename T>
        Value* _EmitUnaryIns(Instruction::OpCode op, Value* v);
        template<typename T>
        Value* _EmitUnaryIns(Instruction::OpCode op, Value* v, Value* result);
        template<typename T>
        Value* _EmitBinaryIns(Instruction::OpCode op, Value* v1, Value* v2);

        template<typename T>
        Value* _EmitBinaryIns(Instruction::OpCode op, Value* v1, Value* v2, Value* vResult);

    private:
        template<typename T, typename U = typename std::enable_if<std::is_base_of<Instruction,T>::value>::type >
        T* _AddInsToIRContext(T* ins);

        Instruction* _CheckTypeIsCompatibleWithReturn(Instruction::OpCode op, Value* v1, Value* v2);
        Instruction* _CheckTypeIsCompatibleWithReturn(Instruction::OpCode op, Value* v1, Value* v2, Value* retValue);
        
        bool _CheckTypeIsCompatibleWithReturn(Instruction::OpCode op, Type* t1,Type*  retType );
        bool _CheckTypeIsCompatibleWithReturn(Instruction::OpCode op, Type* t1,Type* t2, Type* retType);
    private:
        std::shared_ptr<IR::IRContext> m_context;
    };
}