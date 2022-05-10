#pragma once
#include "Frontend/AST/Ast.h"
namespace AST {
    class IASTVisitor {
    public:
        virtual void visitProgram(AST::AstProgram *) = 0;
        virtual void visitFunction(AST::AstFunction *) = 0;
        virtual void visitForStmt( AST::AstForStmt*) = 0;
        virtual void visitWhileStmt( AST::AstWhileStmt * ) = 0;
        virtual void visitDoWhileStmt( AST::AstDoWhileStmt *) = 0;
        virtual void visitIfStmt( AST::AstIfStmt* ) = 0;
        virtual void visitElseStmt( AST::AstElseStmt *) = 0;
        virtual void visitStmts( AST::AstStmts* ) = 0;
        virtual void visitReturnStmt( AST::AstReturnStmt* ) = 0;
        virtual void visitBreakStmt( AST::AstBreakStmt* ) = 0;
        virtual void visitContinueStmt( AST::AstContinueStmt* ) = 0;
        virtual void visitExprStmt( AST::AstExprStmt* ) = 0;
        virtual void visitType(AST::AstType*) = 0;
        virtual void visitFunctionBody(AST::AstFunctionBody*) = 0;
        virtual void visitParamList(AST::AstParamList * ) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceBinaryOpExpr( AST::AstBinaryOpExpr* ) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceUnaryOpExpr(AST::AstUnaryOpExpr* ) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceConditionExpr( AST::AstConditionExpr* ) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceExprs( AST::AstExprs *) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceObjectExpr(AST::AstObjectExpr*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceVoidExpr( AST::AstVoidExpr* ) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceTemp( AST::AstTemp *) = 0;
    } ;

}