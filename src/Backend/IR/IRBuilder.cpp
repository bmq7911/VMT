#pragma once
#include "Backend/IR/IRBuilder.h"
namespace IR {


    IRBuilder::IRBuilder(std::shared_ptr<IR::IRContext>& context)
        : m_context(context)
    {}
    IRBuilder::~IRBuilder() {
    }

    Constant* IRBuilder::createConstant(Type const* type, float value) {
        return new FloatConstant(type, value);
    }

    Constant* IRBuilder::createConstant(Type const* type, double value) {
        return new FloatConstant(type, value);
    }

    
    void IRBuilder::emitBinaryOpIns(IR::Instruction::OpCode op, Value* result, Value* op1, Value* op2) {
        _EmitBinaryIns<BinaryOpIns>(op, op1, op2, result );
    }

    Value* IRBuilder::emitBinaryOpIns(IR::Instruction::OpCode op,  Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(op, v1, v2);
    }

    Value* IRBuilder::emitUnaryOpIns(IR::Instruction::OpCode op, Value* v) {
        return _EmitUnaryIns<UnaryOpIns>( op, v);
    }


    Value* IRBuilder::emitAlloc(const Type* type, const char* name) {
        auto cfunc = m_context->getCurrentFunction();
        auto ins = _AddInsToIRContext(IR::allocator<AllocIns>().alloc( name, type));
        return ins->getRetValue();
    }
    
    Value* IRBuilder::emitAssign(Value* src, Value* dst) {
        auto cfunc = m_context->getCurrentFunction( );
        auto ins = _AddInsToIRContext(IR::allocator<AssignIns>().alloc( src, dst ));
        src->setInstruction(ins);
        return ins->getRetValue();
    }

    Br* IRBuilder::emitBr(Value* v, const char* trueLabel, const char* falseLabel) {
        IR::Br* br = IR::allocator<IR::Br>().alloc(v, trueLabel, falseLabel);
        _AddInsToIRContext(br);
        return br;
    }

    Br* IRBuilder::emitBr(Value* v, std::string const& trueLabel, std::string const& falseLabel) {
        IR::Br* br = IR::allocator<IR::Br>().alloc(v, trueLabel, falseLabel);
        _AddInsToIRContext(br);
        return br;
    }

    Jmp* IRBuilder::emitJmp(const char* label) {
        IR::Jmp* jmp = IR::allocator<IR::Jmp>().alloc(label);
        _AddInsToIRContext(jmp);
        return jmp;
    }
    Jmp* IRBuilder::emitJmp(std::string const& label) {
        IR::Jmp* jmp = IR::allocator<IR::Jmp>().alloc(label);
        _AddInsToIRContext(jmp);
        return jmp;
    }

    Ret* IRBuilder::emitRet(Value* v) {
        IR::Ret* ret = IR::allocator<IR::Ret>().alloc( v );
        _AddInsToIRContext(ret);
        return ret;
    }

    Label* IRBuilder::emitLabel(std::string const& label) {
        auto cfunc = m_context->getCurrentFunction();
        if (nullptr != cfunc->findLabel(label)) {
            return nullptr;
        }
        else {
            auto ins = _AddInsToIRContext(IR::allocator<Label>().alloc(label));
            cfunc->insertLabel(label, ins);
            
            return ins;
        }
    }
    Label* IRBuilder::emitLabel(const char* label) {
        auto cfunc = m_context->getCurrentFunction();
        if (nullptr != cfunc->findLabel(label)) {
            return nullptr;
        }
        else {
            auto ins = _AddInsToIRContext(IR::allocator<Label>().alloc(label));
            cfunc->insertLabel(label, ins);
            return ins;
        }
    }


    Value* IRBuilder::emitSin(Value* v) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kSin, v);
    
    }



    Value* IRBuilder::emitCos(Value* v) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kCos, v);
    }


    Value* IRBuilder::emitTan(Value* v) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kTan, v);
    }



    Value* IRBuilder::emitAdd(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kAdd, v1, v2);
    }

    Value* IRBuilder::emitMinus(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kMinus, v1, v2);

    }


    Value* IRBuilder::emitMul(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kMul, v1, v2);
    }

    Value* IRBuilder::emitDiv(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kDiv, v1, v2);
    }


    Value* IRBuilder::emitMod(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kMod, v1, v2);
    }



    Value* IRBuilder::emitAnd(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kAnd, v1, v2);
    }



    Value* IRBuilder::emitOr(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kOr, v1, v2);
    }



    Value* IRBuilder::emitBitAnd(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kAdd, v1, v2);
    }



    Value* IRBuilder::emitBitOr(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kBitOr, v1, v2);
    }




    Value* IRBuilder::emitBitXor(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kBitXor, v1, v2);
    }


    Value* IRBuilder::emitDot(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kDot, v1, v2);
    }


    Value* IRBuilder::emitCross(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kCross, v1, v2);
    }


    Value* IRBuilder::emitTransposiont(Value* v) {
        return _EmitUnaryIns<UnaryOpIns>(IR::Instruction::OpCode::kT, v);
    }


    Value* IRBuilder::emitInvert(Value* v) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kInvert, v);
    }


    Function* IRBuilder::emitFunction(const char* name, FunctionType* type) {
        auto func = IR::allocator<Function>().alloc(name, type);
        m_context->addFunction(func);
        return func;
    }

    template<typename T>
    Value* IRBuilder::_EmitUnaryIns(Instruction::OpCode op, Value* v) {
        if (false == Instruction::isUnaryOp(op)) {
            return nullptr;
        }
        else {
            auto cfunc = m_context->getCurrentFunction();
        
            std::string valueName = "valueName";
            IR::Value* result = emitAlloc(v->getType(), valueName.c_str());
            auto ins = _AddInsToIRContext(IR::allocator<T>().alloc(op, v, result));
            if (nullptr != result) {
                v->addUser( result);
            }
            return ins->getRetValue();
        }
    }

    template<typename T>
    Value* IRBuilder::_EmitUnaryIns(Instruction::OpCode op, Value* v,Value * result) {
        if (false == Instruction::isUnaryOp(op)) {
            return nullptr;
        }
        else {
            auto ins = _AddInsToIRContext(IR::allocator<T>().alloc(op, v, result));
            auto result = ins->getRetValue();
            if (nullptr != result) {
                v->addUser(result);
            }
            return ins->getRetValue();
        }
    }

    template<typename T>
    Value* IRBuilder::_EmitBinaryIns(Instruction::OpCode op, Value* v1, Value* v2 ) {
        if (false == Instruction::isBinaryOp(op)) {
            return nullptr;
        }
        else {
            auto cfunc = m_context->getCurrentFunction( );
            std::string valueName = "valueName";
            IR::Value * result = emitAlloc(v1->getType(),valueName.c_str() );
            auto ins = _AddInsToIRContext(IR::allocator<T>().alloc(op, v1, v2, result));
            if (nullptr != result) {
                cfunc->insertValue( result);
                v1->addUser( result);
                v2->addUser( result);
            }
            return result;
        }
    }
    
    template<typename T>
    Value* IRBuilder::_EmitBinaryIns( Instruction::OpCode op, Value* v1, Value* v2, Value * result ) {
        if (false == Instruction::isBinaryOp(op)) {
            return nullptr;
        }
        else {
            auto ins = _AddInsToIRContext(IR::allocator<T>().alloc(op,v1, v2, result));
            if (nullptr != result) {
                v1->addUser( result);
                v2->addUser( result);
            }
            return result;
        }
    }

    template<typename T, typename U  >
    T* IRBuilder::_AddInsToIRContext(T * ins) {
        m_context->_IRBuilder_PushIns( static_cast<IR::Instruction*>(ins) );
        return ins;
    }


 
}