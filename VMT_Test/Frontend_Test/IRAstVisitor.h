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
namespace TS {
    /// 把信息通过这样一个对象来进行传递


    class AST_IR_Codegen  : public std::enable_shared_from_this<AST_IR_Codegen>, public AST::IASTVisitor {
    public:
        AST_IR_Codegen() {
            m_context = std::make_shared<IR::IRContext>();
            m_env = std::make_shared<ENV::Env>( );
        }
        void visitFunction(AST::AstFunction* astFunction) {
            std::shared_ptr<ENV::Env> env = std::make_shared<ENV::Env>( );
            env->mount(_GetCurrentEnv());

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
               
                if (!envType) {
                    auto type = m_context->getTypeManger().getTypeFromName( envType->getSymbolName().data() );
                    IR::Value* value = IR::IRBuilder( m_context ).emitAlloc( type , typeTok.toStringView().data() );
                    ir_function->addArgs(value);
                }
            }
            auto block = astFunction->getFunctionBlock();
            block->gen(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this());
            env->unmount();
        }
        void visitForStmt(AST::AstForStmt*) override {}
        void visitWhileStmt(AST::AstWhileStmt*) override {}
        void visitDoWhileStmt(AST::AstDoWhileStmt*) override {}
        void visitIfStmt(AST::AstIfStmt*) override {}
        void visitElseStmt(AST::AstElseStmt*) override {}
        void visitStmts(AST::AstStmts*) override {}
        void visitReturnStmt(AST::AstReturnStmt*) override {}
        void visitBreakStmt(AST::AstBreakStmt*) override {}
        void visitContinueStmt(AST::AstContinueStmt*) override {}
        void visitExprStmt(AST::AstExprStmt* astExprStmt) override {
            auto expr = astExprStmt->getExpr( );
            expr->reduce( std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this());
        }
        void visitType(AST::AstType*) override {}
        void visitParamList(AST::AstParamList*) override {}
        void visitBlock(AST::AstBlock* astBlock) override {
            std::shared_ptr<ENV::Env> env = std::make_shared<ENV::Env>();
            env->mount(_GetCurrentEnv());
            for (auto iter = astBlock->begin(); iter != astBlock->end(); ++iter) {
                (*iter)->gen( std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this() );
            }
            env->unmount();
        }
        std::shared_ptr<AST::AstObjectExpr> reduceBinaryOpExpr(AST::AstBinaryOpExpr* astBinaryOpExpr ) override {
            auto leftExpr = astBinaryOpExpr->getLeft( );
            auto rightExpr = astBinaryOpExpr->getRight( );
            //
            auto rleftExpr = leftExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this());
            auto rrightExpr = rightExpr->reduce(std::enable_shared_from_this<AST_IR_Codegen>::shared_from_this());
            
            IR::Instruction::OpCode op = _GetBinaryOpCode(astBinaryOpExpr->getOp());
            IR::BinaryOpIns* binaryOpIns = IR::IRBuilder(m_context).emitBinaryOpIns();
        }
        std::shared_ptr<AST::AstObjectExpr> reduceUnaryOpExpr(AST::AstUnaryOpExpr*) override {}
        std::shared_ptr<AST::AstObjectExpr> reduceConditionExpr(AST::AstConditionExpr*) override {}
        std::shared_ptr<AST::AstObjectExpr> reduceObjectExpr(AST::AstObjectExpr*) override {}
        std::shared_ptr<AST::AstObjectExpr> reduceVoidExpr(AST::AstVoidExpr*) override {}
        std::shared_ptr<AST::AstObjectExpr> reduceTemp(AST::AstTemp*) override {}
        std::shared_ptr<AST::AstObjectExpr> reduceDecl(AST::AstDecl*) override{}
        std::shared_ptr<AST::AstObjectExpr> reduceDecls(AST::AstDecls*) override {}
        std::shared_ptr<AST::AstObjectExpr> reduceAssign(AST::AstAssign*) override {}
    private:
        IR::Instruction::OpCode _GetBinaryOpCode(Token tok) const {
            
        }
        IR::Type* _GetType(std::string_view const& str_view) const{
            return m_context->getTypeManger().getTypeFromName(str_view );
        }
        std::shared_ptr<ENV::Env> _GetCurrentEnv() const {
            return m_currentEnv;
        }
    private:
        std::shared_ptr<ENV::Env>      m_env;
        std::shared_ptr<ENV::Env>      m_currentEnv;
        std::shared_ptr<IR::IRContext> m_context;
    };

}