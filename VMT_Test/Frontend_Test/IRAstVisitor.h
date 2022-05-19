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
	class IRAstVisitor : public AST::IASTVisitor {
	public:
        void visitProgram(AST::AstProgram*) {
            m_topEnv = std::make_shared<ENV::Env>();
            std::shared_ptr<ENV::BoolType>              typeBool = std::make_shared<ENV::BoolType>(std::string_view("bool"));
            std::shared_ptr<ENV::IntegerType<int32_t>>  typeI32 = std::make_shared<ENV::IntegerType<int32_t>>(std::string_view("i32"), typeBool);
            std::shared_ptr<ENV::IntegerType<uint32_t>> typeUI32 = std::make_shared<ENV::IntegerType<uint32_t>>(std::string_view("ui32"), typeBool);
            std::shared_ptr<ENV::RealType<float>>       typeF32 = std::make_shared<ENV::RealType<float>>(std::string_view("f32"), typeBool);
            std::shared_ptr<ENV::RealType<double>>      typeF64 = std::make_shared<ENV::RealType<double>>(std::string_view("f64"), typeBool);
            m_topEnv->put(typeI32);
            m_topEnv->put(typeUI32);
            m_topEnv->put(typeF32);
            m_topEnv->put(typeF64);
            m_topEnv->put(typeBool);
            m_currentEnv = m_topEnv;
        }
        void visitFunction(AST::AstFunction* astFunction ) {
            std::shared_ptr<ENV::Env> env = std::make_shared<ENV::Env>();
            env->mount( m_topEnv );
            m_currentEnv = env;

            std::shared_ptr<AST::AstType> type = astFunction->getFunctionType( );
            IR::Function* function = IR::allocator<IR::Function>().alloc();
            function->getFunctionName();
            m_currentFunction = function;
            type->gen( std::enable_shared_from_this<IRAstVisitor>::shared_from_this() );
            
    


            env->unmount();
        }
        void visitForStmt(AST::AstForStmt*) {
        
        }
        void visitWhileStmt(AST::AstWhileStmt*) {
        
        }
        void visitDoWhileStmt(AST::AstDoWhileStmt*) {
        
        }
        void visitIfStmt(AST::AstIfStmt*) {
        
        }
        void visitElseStmt(AST::AstElseStmt*) {
        
        }
        void visitStmts(AST::AstStmts*) {
        
        }
        void visitReturnStmt(AST::AstReturnStmt*) {
        
        }
        void visitBreakStmt(AST::AstBreakStmt*) {
        
        }
        void visitContinueStmt(AST::AstContinueStmt*) {
        
        }
        void visitExprStmt(AST::AstExprStmt*) {
        
        }
        void visitType(AST::AstType* type) {
            auto ptype = m_currentEnv->find( type->getType().toStringView(), ENV::SymbolType::kType);
            if (!ptype) {
                Diagnose::errorMsg("the type not define");
            }



            
        }
        void visitFunctionBody(AST::AstFunctionBody*) {
        
        }
        void visitParamList(AST::AstParamList*) {
        
        }
        void visitBlock(AST::AstBlock*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceBinaryOpExpr(AST::AstBinaryOpExpr*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceUnaryOpExpr(AST::AstUnaryOpExpr*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceConditionExpr(AST::AstConditionExpr*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceExprs(AST::AstExprs*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceObjectExpr(AST::AstObjectExpr*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceVoidExpr(AST::AstVoidExpr*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceTemp(AST::AstTemp*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceDecl(AST::AstDecl*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceDecls(AST::AstDecls*) {
        
        }
        std::shared_ptr<AST::AstObjectExpr> reduceAssign(AST::AstAssign*) {
        
        }

	private:
        IR::Function* m_currentFunction;
		std::shared_ptr<IR::IRContext> m_constext;
        std::shared_ptr<ENV::Env>      m_topEnv;
        std::shared_ptr<ENV::Env>      m_currentEnv;
	};


}