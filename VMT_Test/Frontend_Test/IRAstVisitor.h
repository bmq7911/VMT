#pragma once
#include "Frontend/AST/AstVisitor.h"
#include "Backend/IR/IRContext.h"
#include "SymbolTable/Symbol.h"
#include "SymbolTable/Env.h"
#include "Diagnose/Diagnose.h"
#include "SymbolTable/ObjectId.h"
#include "SymbolTable/IntegerType.h"
#include "SymbolTable/RealType.h"
#include "SymbolTable/BoolType.h"
#include "Backend/IR/IRBuilder.h"
#include <iostream>

namespace TS {

    class CollectIRValue : public AST::ICollectInfoBack {
    public:
        CollectIRValue() 
            : m_value( nullptr )
        {}

        IR::Value* getValue() const {
            return m_value;
        }
        void setValue(IR::Value * v) {
            m_value = v;
        }
    private:
	    IR::Value* m_value;
    };

    class AST_IR_Codegen  : public std::enable_shared_from_this<AST_IR_Codegen>, public AST::IASTVisitor {
    public:
        AST_IR_Codegen() {
            m_context = std::make_shared<IR::IRContext>();
            m_env = std::make_shared<ENV::Env>( );	
            std::shared_ptr<ENV::BoolType>              typeBool = std::make_shared<ENV::BoolType>(std::string_view("bool"));
		    std::shared_ptr<ENV::IntegerType<int32_t>>  typeI32  = std::make_shared<ENV::IntegerType<int32_t>>( std::string_view("i32"), typeBool );
		    std::shared_ptr<ENV::IntegerType<uint32_t>> typeUI32 = std::make_shared<ENV::IntegerType<uint32_t>>(std::string_view("ui32"), typeBool );
		    std::shared_ptr<ENV::RealType<float>>       typeF32  = std::make_shared<ENV::RealType<float>>(std::string_view("f32"), typeBool );
		    std::shared_ptr<ENV::RealType<double>>      typeF64  = std::make_shared<ENV::RealType<double>>(std::string_view("f64"), typeBool);
		    m_env->put(typeI32);
		    m_env->put(typeUI32);
		    m_env->put(typeF32);
		    m_env->put(typeF64);
		    m_env->put(typeBool);
		    m_currentEnv = m_env;
        }

        void visitFunction(AST::AstFunction* astFunction, AST::ICollectInfoBack * collect ) {
            std::shared_ptr<ENV::Env> env = std::make_shared<ENV::Env>( );
            ENV::EnvRAII lock( env, _GetCurrentEnv());
            _SetCurrentEnv(env);
            auto funNameTok= astFunction->getFunctionName();
            IR::Function* ir_function = IR::IRBuilder(m_context).emitFunction( funNameTok.toStringView().data(), nullptr );

            auto astType = astFunction->getFunctionType();
            auto envType = env->find(astType->getType().toStringView(), ENV::SymbolType::kType);
            if (!envType) {
                Diagnose::errorMsg( "cann't find the type");
                return;
            }
            auto paramList = astFunction->getFunctionParamList( );
            for (size_t i = 0; i < paramList->size(); ++i) {
                auto param = paramList->at(i);
                auto typeTok = param.getType();
                auto envType = env->find(typeTok.toStringView(), ENV::SymbolType::kType);
                auto name = param.getId( );
                if (envType) {
                    auto type = m_context->getTypeManger().getTypeFromName( envType->getSymbolName().data() );
                    IR::Value* value = IR::IRBuilder( m_context ).emitAlloc( type , std::string(name.toStringView()).c_str() );
                    env->put(std::string(name.toStringView()), value);
                    ir_function->addArgs(value);
                }
                else {
                    Diagnose::errorMsg("cann't find the type");
                    return;
                }
            }
            auto block = astFunction->getFunctionBlock();
            block->gen(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), collect );

            {
                auto function = m_context->getCurrentFunction();
                for (auto iter = function->begin(); iter != function->end(); iter->getNext()) {
                    std::cout << iter->getOpStr() << std::endl;
                }
            }
        }

        void visitForStmt(AST::AstForStmt*, AST::ICollectInfoBack* collect) override {
        
        }

        void visitWhileStmt(AST::AstWhileStmt*, AST::ICollectInfoBack* collect) override {
        
        }

        void visitDoWhileStmt(AST::AstDoWhileStmt*, AST::ICollectInfoBack* collect) override {
        
        }

        void visitIfStmt(AST::AstIfStmt*, AST::ICollectInfoBack* collect) override {
        
        }

        void visitElseStmt(AST::AstElseStmt*, AST::ICollectInfoBack* collect) override {}
        void visitStmts(AST::AstStmts*, AST::ICollectInfoBack* collect) override {}
        void visitReturnStmt(AST::AstReturnStmt* ,AST::ICollectInfoBack* collect) override {}
        void visitBreakStmt(AST::AstBreakStmt*, AST::ICollectInfoBack* collect) override {}
        void visitContinueStmt(AST::AstContinueStmt*, AST::ICollectInfoBack* collect) override {}
        void visitExprStmt(AST::AstExprStmt* astExprStmt, AST::ICollectInfoBack* collect) override {
            auto expr = astExprStmt->getExpr( );
            CollectIRValue collectValue;
            expr->reduce( std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
        }
        void visitType(AST::AstType*, AST::ICollectInfoBack* collect) override {}
        void visitParamList(AST::AstParamList*, AST::ICollectInfoBack* collect) override {}
        void visitBlock(AST::AstBlock* astBlock, AST::ICollectInfoBack* collect) override {
            std::shared_ptr<ENV::Env> env = std::make_shared<ENV::Env>();
            ENV::EnvRAII s( env, _GetCurrentEnv());
            _SetCurrentEnv(env);
            m_currentEnv = env;
            for (auto iter = astBlock->begin(); iter != astBlock->end(); ++iter) {
                (*iter)->gen( std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), collect );
            }
        }


        std::shared_ptr<AST::AstObjectExpr> reduceBinaryOpExpr(AST::AstBinaryOpExpr* astBinaryOpExpr , AST::ICollectInfoBack* collect) override {
            auto leftExpr = astBinaryOpExpr->getLeft( );
            auto rightExpr = astBinaryOpExpr->getRight( );
            CollectIRValue collectValue1;
            CollectIRValue collectValue2;
            auto rleftExpr = leftExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue1);
            auto rrightExpr = rightExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(),&collectValue2);
            auto tok = astBinaryOpExpr->getOp();
            IR::Instruction::OpCode opCode = IR::Instruction::OpCode::kError;
            std::string op = tok.toString();
            struct map {
                const char* str;
                IR::Instruction::OpCode op;

            };
            static const map strOpCode[] = {
                {"+",IR::Instruction::OpCode::kAdd},
                {"-",IR::Instruction::OpCode::kMinus},
                {"*",IR::Instruction::OpCode::kMul},
                {"/",IR::Instruction::OpCode::kDiv},
                {"%",IR::Instruction::OpCode::kMod},
                {"**",IR::Instruction::OpCode::kExp},
            };
            for (size_t i = 0; i < sizeof(strOpCode) / sizeof(strOpCode[0]); ++i) {
                if (op == strOpCode[i].str){
                    opCode = strOpCode[i].op;
                    break;
                }
            }
            auto f = [this,&collectValue1,&collectValue2,&collect ](IR::Instruction::OpCode op1, IR::Instruction::OpCode op2) {
                    IR::Value* v = IR::IRBuilder(m_context).emitBinaryOpIns(IR::Instruction::OpCode::kAdd, collectValue1.getValue(), collectValue2.getValue());
                    IR::Value* v2 = IR::IRBuilder(m_context).emitAssign(collectValue1.getValue(), v);
                    static_cast<CollectIRValue*>(collect)->setValue(v2);
            };
            if (opCode == IR::Instruction::OpCode::kError) {
                if (op == "+=") {
                    f( IR::Instruction::OpCode::kAdd, IR::Instruction::OpCode::kAssign);
                    return nullptr;
                }
                else if (op == "-=") {
                    f(IR::Instruction::OpCode::kMinus, IR::Instruction::OpCode::kAssign);
                    return nullptr;
                }
                else if (op == "*=") {
                    f(IR::Instruction::OpCode::kMul, IR::Instruction::OpCode::kAssign);
                    return nullptr;
                }
                else if (op == "/=") {
                    f(IR::Instruction::OpCode::kDiv, IR::Instruction::OpCode::kAssign);
                    return nullptr;
                }
                else if (op == "%=") {
                    f(IR::Instruction::OpCode::kMod, IR::Instruction::OpCode::kAssign);
                    return nullptr;
                }
                else if (op == "|=") {
                
                }
                else if (op == "&=") {
                
                }
                else if (op == "^=") {
                    
                }
                else if (op == "<<=") {
                
                }
                else if (op == ">>=") {
                
                }
                return nullptr;
            }
            else {

                IR::Value* v = IR::IRBuilder(m_context).emitBinaryOpIns(opCode, collectValue1.getValue(), collectValue2.getValue());
                static_cast<CollectIRValue*>(collect)->setValue(v);
                return nullptr;
            }
        }
        std::shared_ptr<AST::AstObjectExpr> reduceUnaryOpExpr(AST::AstUnaryOpExpr* astUnaryExpr, AST::ICollectInfoBack* collect) override {
            auto rightExpr = astUnaryExpr->getExpr( );
            CollectIRValue collectValue;
            rightExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
            IR::Instruction::OpCode op = _GetUnaryOpCode( astUnaryExpr->getOp() );
            IR::Value* v = IR::IRBuilder(m_context).emitUnaryOpIns(op, collectValue.getValue());
            static_cast<CollectIRValue*>(collect)->setValue(v);
            return nullptr;
        }
        std::shared_ptr<AST::AstObjectExpr> reduceConditionExpr(AST::AstConditionExpr* astConditionExpr, AST::ICollectInfoBack* collect) override {
            auto contitionExpr = astConditionExpr->getCondition( );
            auto trueExpr = astConditionExpr->getTrueExpr( );
            auto falseExpr = astConditionExpr->getFalseExpr( );
            CollectIRValue collectConditionValue;
            contitionExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectConditionValue);
            IR::IRBuilder(m_context).emitBr(  collectConditionValue.getValue(), "cond.true:","cond.false:");
            IR::IRBuilder(m_context).emitLabel("con.start:");
            CollectIRValue collectTrueValue;
                
            trueExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectTrueValue);
            IR::IRBuilder(m_context).emitJmp("con.end:");
            CollectIRValue collectFalseValue;
            falseExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectFalseValue);
            IR::IRBuilder(m_context).emitJmp("cond.end:");

            IR::IRBuilder(m_context).emitLabel("con.end:");
            auto v= IR::IRBuilder(m_context).emitPhi( collectTrueValue.getValue(), collectFalseValue.getValue() );
            static_cast<CollectIRValue*>(collect)->setValue(v);
            return nullptr;
        }

        std::shared_ptr<AST::AstObjectExpr> reduceConstantExpr(AST::AstConstantExpr* astObjectExpr, AST::ICollectInfoBack* collect) override {
            Token tok = astObjectExpr->getToken();
            if (tok.getTokenId() == TokenId::kw_integer) {
                //IR::Value* v = IR::IRBuilder(m_context).emitAlloc(  m_context->getTypeManger().getTypeFromName("i32"), );
                static_cast<CollectIRValue*>(collect)->setValue(new IR::IntegerConstant(m_context->getTypeManger().getTypeFromName("i32"), std::atoi(tok.toString().c_str())));
            }
            else if (tok.getTokenId() == TokenId::kw_real) {
                static_cast<CollectIRValue*>(collect)->setValue(new IR::FloatConstant(m_context->getTypeManger().getTypeFromName("f32"), std::atof(tok.toString().c_str())));
            }
            else if (tok.getTokenId() == TokenId::kw_true) {
                static_cast<CollectIRValue*>(collect)->setValue(new IR::TrueConstant( m_context->getTypeManger().getTypeFromName("bool")));
            }
            else if (tok.getTokenId() == TokenId::kw_false) {
                static_cast<CollectIRValue*>(collect)->setValue(new IR::FalseConstant(m_context->getTypeManger().getTypeFromName("bool")));
            }
            else {
                _ASSERT(false);
            }
            return nullptr;
        }

        std::shared_ptr<AST::AstObjectExpr> reduceObjectExpr(AST::AstObjectExpr* astObjectExpr, AST::ICollectInfoBack* collect) override {
            /// 这里最重要的逻辑就是查询当前已分配的节点数据,也就是IValue
            CollectIRValue collectValue;
            auto env = _GetCurrentEnv( );
            auto value = env->find( std::string(astObjectExpr->getObject().toStringView()));
            if (nullptr != value) {
                static_cast<CollectIRValue*>(collect)->setValue(value);
            }
            else {
                Diagnose::errorMsg("can not find the value");
            }
            return nullptr;
        }
        
        std::shared_ptr<AST::AstObjectExpr> reduceVoidExpr(AST::AstVoidExpr* astVoidExpr, AST::ICollectInfoBack* collect) override {
            CollectIRValue collectValue;
            astVoidExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
            return nullptr;
        }

        // decl ::= type variable;
        //      ::= type variable = expr
        //      AstDecl -> type variable AssignExpr( variable,expr )
        std::shared_ptr<AST::AstObjectExpr> reduceDecl(AST::AstDecl* astDecl, AST::ICollectInfoBack* collect) override{
            auto env = _GetCurrentEnv( );
            auto envType = env->find(astDecl->getType().toStringView(), ENV::SymbolType::kType);
            IR::Value* v = nullptr;
            if (!envType) {
                Diagnose::errorMsg("can not find the type");
            }
            else {
                auto type = m_context->getTypeManger().getTypeFromName(envType->getSymbolName());
                std::string str(astDecl->getName().toStringView());
                v = IR::IRBuilder(m_context).emitAlloc( type, str.c_str() );
                env->put( str, v );
            }
            auto expr = astDecl->getExpr();
            CollectIRValue collectValue;
            if (expr) {
                expr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
            }
            static_cast<CollectIRValue*>(collect)->setValue( v );
            return nullptr;
        }

        std::shared_ptr<AST::AstObjectExpr> reduceDecls(AST::AstDecls* astDecls, AST::ICollectInfoBack* collect) override {
            CollectIRValue collectValue;
            for (auto iter = astDecls->begin(); iter != astDecls->end(); ++iter) {
                (*iter)->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(),&collectValue );
            }
            static_cast<CollectIRValue*>(collect)->setValue(collectValue.getValue());
            return nullptr;
        }
        
        // 这条语句很特殊,因为完成了定值操作
        std::shared_ptr<AST::AstObjectExpr> reduceAssign(AST::AstAssign* astAssign, AST::ICollectInfoBack* collect) override {
            auto env = _GetCurrentEnv( );
            CollectIRValue collectValue;
            astAssign->getExpr()->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue );

            auto tok = astAssign->getToken( );
            auto value = env->find( std::string(tok.toStringView()));
            if (nullptr != value) {
                auto v = IR::IRBuilder(m_context).emitAssign(value, collectValue.getValue());
                env->put(std::string(tok.toStringView()), v);
            }
            return nullptr;
        }
        std::shared_ptr<AST::AstObjectExpr> reduceExprs(AST::AstExprs* astExprs, AST::ICollectInfoBack* collect) override {
            CollectIRValue collectValue;
            for (auto iter = astExprs->begin(); iter != astExprs->end(); ++iter) {
                (*iter)->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this(), &collectValue);
            }
            static_cast<CollectIRValue*>(collect)->setValue(collectValue.getValue());
            return nullptr;
        }

    private:
        IR::Instruction::OpCode _GetBinaryOpCode(Token tok) const {
            return IR::Instruction::getOpCode(tok.toStringView());
        }
        IR::Instruction::OpCode _GetUnaryOpCode(Token tok) const {
            return IR::Instruction::getOpCode(tok.toStringView());
        }
        IR::Type* _GetType(std::string_view const& str_view) const{
            return m_context->getTypeManger().getTypeFromName(str_view );
        }
        std::shared_ptr<ENV::Env> _GetCurrentEnv() const {
            return m_currentEnv;
        }
        void _SetCurrentEnv(std::shared_ptr<ENV::Env> env) {
            m_currentEnv = env;
        }
        
    private:

        std::shared_ptr<ENV::Env>      m_env;
        std::shared_ptr<ENV::Env>      m_currentEnv;
        std::shared_ptr<IR::IRContext> m_context;
    };

}