#pragma once
#include "Frontend/AST/AST.h"
namespace AST {
    class IASTVisitor {
    public:
        virtual void visitProgram(std::shared_ptr<AST::Program>) = 0;
        virtual void visitFuntion(std::shared_ptr<AST::Function>) = 0;
        virtual void visitForStmt( std::shared_ptr<AST::ForStmt> ) = 0;
        virtual void visitWhileStmt(std::shared_ptr<AST::WhileStmt>) = 0;
        virtual void visitDoWhileStmt(std::shared_ptr<AST::DoWhileStmt>) = 0;
        virtual void visitIfStmt(std::shared_ptr<AST::IfStmt>) = 0;
        virtual void visitElseStmt(std::shared_ptr<AST::ElseStmt>) = 0;
        virtual void visitStmts(std::shared_ptr<AST::Stmts>) = 0;
        virtual void visitReturnStmt(std::shared_ptr<AST::ReturnStmt>) = 0;
        virtual void visitBreakStmt(std::shared_ptr<AST::BreakStmt>) = 0;
        virtual void visitContinueStmt(std::shared_ptr<AST::ContinueStmt>) = 0;
        virtual void visitExprStmt( std::shared_ptr<AST::ExprStmt> ) = 0;

        virtual std::shared_ptr<AST::ObjectExpr> reduceBinaryOpExpr(std::shared_ptr<AST::BinaryOpExpr>) = 0;
        virtual std::shared_ptr<AST::ObjectExpr> reduceUnaryOpExpr(std::shared_ptr<AST::UnaryOpExpr>) = 0;
        virtual std::shared_ptr<AST::ObjectExpr> reduceConditionExpr(std::shared_ptr<AST::ConditionExpr>) = 0;
        virtual std::shared_ptr<AST::ObjectExpr> reduceExprs( std::shared_ptr<AST::Exprs> ) = 0;
        virtual std::shared_ptr<AST::ObjectExpr> reduceObjectExpr(std::shared_ptr<AST::ObjectExpr>) = 0;
        virtual std::shared_ptr<AST::ObjectExpr> reduceVoidExpr( std::shared_ptr<AST::VoidExpr>) = 0;
        virtual std::shared_ptr<AST::ObjectExpr> reduceTemp(std::shared_ptr<AST::Temp>) = 0;
    } ;
}