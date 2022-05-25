#pragma once
#include "Backend/IR/IRBuilder.h"
namespace IR {

    /// 1.Í¨ï¿½ï¿½ï¿½Å±ï¿½ÏµÍ³ï¿½ï¿½Êµï¿½ï¿½
    /// 2.ï¿½Å»ï¿½ï¿½ï¿½ï¿½ï¿½ÒªÄ¿ï¿½ï¿½ï¿½ï¿½Ê²Ã´,ï¿½ï¿½ï¿½ï¿½ï¿½Ú²ï¿½Ó°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½ï¿½Â¼ï¿½ï¿½ï¿½Ö¸ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
    /// ï¿½ï¿½ï¿½ï¿½ï¿½È²ï¿½ï¿½ï¿½ï¿½ï¿½IRBuilder

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


    Value* IRBuilder::emitBinaryOpIns(IR::Instruction::OpCode op,  Value* v1, Value* v2) {
        std::string name = m_context->getCurrentFunction()->getNameAlloc()->allocTemporaryName();
        IR::Value* t = new IR::Value( name.c_str(),v1->getType(), nullptr );
        auto ins = _AddInsToIRContext(IR::allocator<BinaryOpIns>().alloc(op, nullptr,v1->getType(), v1,v2));
        t->setInstruction(ins);
        return ins->getRetValue();
    }

    Value* IRBuilder::emitUnaryOpIns(IR::Instruction::OpCode op, Value* v) {
        std::string name = m_context->getCurrentFunction()->getNameAlloc()->allocTemporaryName();
        IR::Value* t = new IR::Value( name.c_str(),v->getType(), nullptr );
        auto ins = _AddInsToIRContext(IR::allocator<UnaryOpIns>().alloc(op, nullptr, v->getType(), v));
        t->setInstruction(ins);
        return ins->getRetValue( );
    }


    Value* IRBuilder::emitAlloc(const Type* type, const char* name) {
        auto cfunc = m_context->getCurrentFunction();
        std::shared_ptr<NameAlloc> nameAlloc;
        if (nullptr == cfunc) {
            nameAlloc = m_context->getNameAlloc();
        }
        else {
            nameAlloc = cfunc->getNameAlloc();
        }
        auto ins = _AddInsToIRContext(IR::allocator<AllocIns>().alloc(nameAlloc->allocName(name), type));
        return ins->getRetValue();
    }
    
    /// ÕâÌõÖ¸ÁîºÜÌØÊâ,ÒòÎªÖ»ÓÐÕâÌõÖ¸Áî²ÅÄÜÏòÒ»¸öÃüÃûµÄvalue¸³Öµ
    Value* IRBuilder::emitAssign(Value* src, Value* dst) {
        auto cfunc = m_context->getCurrentFunction( );
        std::shared_ptr<NameAlloc> nameAlloc;
        if (nullptr == cfunc) {
            nameAlloc = m_context->getNameAlloc( );
        }
        else {
            nameAlloc = m_context->getNameAlloc( );
        }
        auto ins = _AddInsToIRContext(IR::allocator<AssignIns>().alloc( src, dst ));
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

    Value* IRBuilder::emitSin(Value* v, const char* name) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kSin, v, name);
    }


    Value* IRBuilder::emitCos(Value* v) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kCos, v);
    }

    Value* IRBuilder::emitCos(Value* v, const char* name) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kCos, v, name);
    }

    Value* IRBuilder::emitTan(Value* v) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kTan, v);
    }

    Value* IRBuilder::emitTan(Value* v, const char* name) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kTan, v, name);
    }


    Value* IRBuilder::emitAdd(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kAdd, v1, v2);
    }
    Value* IRBuilder::emitAdd(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kAdd, v1, v2, name);
    }

    void IRBuilder::emitAdd(Value* v1, Value* v2, Value* result ) {

    }
    Value* IRBuilder::emitMinus(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kMinus, v1, v2);

    }

    Value* IRBuilder::emitMinus(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kMinus, v1, v2, name);
    }

    Value* IRBuilder::emitMul(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kMul, v1, v2, name);
    }

    Value* IRBuilder::emitDiv(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kDiv, v1, v2);
    }

    Value* IRBuilder::emitDiv(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kDiv, v1, v2, name);
    }

    Value* IRBuilder::emitMod(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kMod, v1, v2);
    }

    Value* IRBuilder::emitMod(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kMod, v1, v2, name);
    }


    Value* IRBuilder::emitAnd(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kAnd, v1, v2);
    }

    Value* IRBuilder::emitAnd(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kAnd, v1, v2, name);
    }


    Value* IRBuilder::emitOr(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kOr, v1, v2);
    }

    Value* IRBuilder::emitOr(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kOr, v1, v2, name);
    }


    Value* IRBuilder::emitBitAnd(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kAdd, v1, v2);
    }

    Value* IRBuilder::emitBitAnd(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kAdd, v1, v2, name);
    }


    Value* IRBuilder::emitBitOr(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kBitOr, v1, v2);
    }

    Value* IRBuilder::emitBitOr(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kBitOr, v1, v2, name);
    }



    Value* IRBuilder::emitBitXor(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kBitXor, v1, v2);
    }

    Value* IRBuilder::emitBitXor(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kBitXor, v1, v2, name);
    }

    Value* IRBuilder::emitDot(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kDot, v1, v2);
    }

    Value* IRBuilder::emitDot(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kDot, v1, v2, name);
    }

    Value* IRBuilder::emitCross(Value* v1, Value* v2) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kCross, v1, v2);
    }

    Value* IRBuilder::emitCross(Value* v1, Value* v2, const char* name) {
        return _EmitBinaryIns<BinaryOpIns>(Instruction::OpCode::kCross, v1, v2, name);
    }

    Value* IRBuilder::emitTransposiont(Value* v) {
        return _EmitUnaryIns<UnaryOpIns>(IR::Instruction::OpCode::kT, v);
    }

    Value* IRBuilder::emitTransposiont(Value* v, const char* name) {
        return _EmitUnaryIns<UnaryOpIns>(IR::Instruction::OpCode::kT, v, name);
    }

    Value* IRBuilder::emitInvert(Value* v) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::OpCode::kInvert, v);
    }

    Value* IRBuilder::emitInvert(Value* v, const char* name) {
        return _EmitUnaryIns<UnaryOpIns>(Instruction::kInvert, v, name);
    }

    Function* IRBuilder::emitFunction(const char* name, FunctionType* type) {
        auto func = IR::allocator<Function>().alloc(name, type);
        m_context->addFunction(func);
        return func;
    }

    template<typename T>
    Value* IRBuilder::_EmitUnaryIns(Instruction::OpCode op, Value* v) {
        return _EmitUnaryIns<T>(op, v, nullptr);
    }

    template<typename T>
    Value* IRBuilder::_EmitUnaryIns(Instruction::OpCode op, Value* v, const char* name) {
        if (false == Instruction::isUnaryOp(op)) {
            return nullptr;
        }
        else {
            if (auto errorIns =_CheckTypeIsCompatibleWithReturn(op, v, v)) {
                auto ins = _AddInsToIRContext(errorIns);
                return ins->getRetValue();
            }
            auto cfunc = m_context->getCurrentFunction();
            std::shared_ptr<NameAlloc> nameAlloc;
            if (nullptr == cfunc) {
                nameAlloc = m_context->getNameAlloc();
            }
            else {
                nameAlloc = cfunc->getNameAlloc();
            }
            std::string valueName;
            if (nullptr == name) {
                valueName = nameAlloc->allocTemporaryName();
            }
            else {
                valueName = nameAlloc->allocName(name);
            }
            auto ins = _AddInsToIRContext(IR::allocator<T>().alloc(op, v->getType(), valueName, v));
            auto value = ins->getRetValue();
            if (nullptr != value) {
                v->addUser(value);
            }
            return ins->getRetValue();
        }
    }

    template<typename T>
    Value* IRBuilder::_EmitBinaryIns(Instruction::OpCode op, Value* v1, Value* v2) {
        return _EmitBinaryIns<T>(op, v1, v2, (const char*)nullptr);
    }


    template<typename T>
    Value* IRBuilder::_EmitBinaryIns(Instruction::OpCode op, Value* v1, Value* v2, const char* name) {
        if (false == Instruction::isBinaryOp(op)) {
            return nullptr;
        }
        else {
            if (auto errorIns = _CheckTypeIsCompatibleWithReturn(op, v1, v2, v1)) {
                auto ins = _AddInsToIRContext(errorIns);
                return ins->getRetValue();
            }
            auto cfunc = m_context->getCurrentFunction();
            std::shared_ptr<NameAlloc> nameAlloc;
            if (nullptr == cfunc) {
                nameAlloc = m_context->getNameAlloc();
            }
            else {
                nameAlloc = cfunc->getNameAlloc();
            }
            std::string valueName;
            if (nullptr == name) {
                valueName = nameAlloc->allocTemporaryName();
            }
            else {
                valueName = nameAlloc->allocName(name);
            }
            auto ins = _AddInsToIRContext(IR::allocator<T>().alloc(op, valueName, v1->getType(), v1, v2));
            auto value = ins->getRetValue( );
            if (nullptr != value) {
                cfunc->insertValue(value);
                v1->addUser(value);
                v2->addUser(value);
            }
            return value;
        }
    }
    
    template<typename T>
    Value* IRBuilder::_EmitBinaryIns( Instruction::OpCode op, Value* v1, Value* v2, Value * vResult ) {
        if (false == Instruction::isBinaryOp(op)) {
            return nullptr;
        }
        else {
            if (auto errorIns = _CheckTypeIsCompatibleWithReturn(op, v1, v2,vResult)) {
                auto ins = _AddInsToIRContext(errorIns);
                return ins->getRetValue();
            }
            auto cfunc = m_context->getCurrentFunction();
            std::shared_ptr<NameAlloc> nameAlloc;
            if (nullptr == cfunc) {
                nameAlloc = m_context->getNameAlloc();
            }
            else {
                nameAlloc = cfunc->getNameAlloc();
            }
            std::string valueName;
            valueName = nameAlloc->allocTemporaryName();
            auto ins = _AddInsToIRContext(IR::allocator<T>().alloc(op, valueName, v1->getType(), v1, v2));
            auto value = ins->getRetValue();
            if (nullptr != value) {
                v1->addUser(value);
                v2->addUser(value);
            }
            return value;
        }
    }

    template<typename T, typename U  >
    T* IRBuilder::_AddInsToIRContext(T * ins) {
        m_context->_IRBuilder_PushIns( static_cast<IR::Instruction*>(ins) );
        return ins;
    }




    Instruction* IRBuilder::_CheckTypeIsCompatibleWithReturn(Instruction::OpCode op, Value* v1, Value* retValue) {
        const Type* t1 = v1->getType();
        Type const* retType = retValue->getType();
        if (retType != t1->isSupportOp(op)) {
            return IR::allocator<ErrorIns>().alloc( );
        }
        else {
            return nullptr;
        }
    }
    
    Instruction* IRBuilder::_CheckTypeIsCompatibleWithReturn(Instruction::OpCode op, Value* v1, Value* v2, Value* retValue) {
        const Type* t1 = v1->getType( );
        const Type* t2 = v2->getType( );
        const Type* retType = retValue->getType( );
        if (t1 == t2) {
            auto ttype= t1->isSupportOp(op);
            if (retType == ttype) {
                return nullptr;
            }
        }
        return IR::allocator<ErrorIns>().alloc();
    }
    
    bool IRBuilder::_CheckTypeIsCompatibleWithReturn(Instruction::OpCode op, Type* t1, Type* retType) {
        if (retType != t1->isSupportOp(op)) {
            return false;
        }
        else {
            return true;
        }

    }

    bool IRBuilder::_CheckTypeIsCompatibleWithReturn(Instruction::OpCode op, Type* t1, Type* t2, Type* retType) {
        if (t1 != t2) {
            return false;
        }
        if (retType != t1->isSupportOp(op)) {
            return false;
        }
        else {
            return true;
        }
    }
 
}