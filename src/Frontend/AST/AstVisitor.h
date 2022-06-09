#pragma once
#include "Frontend/AST/Ast.h"
namespace AST {
    class ICollectInfoBack {
        
    };
    class IASTVisitor {
    public:
        virtual void visitFunction(AST::AstFunction* ,AST::ICollectInfoBack* ) = 0;
        virtual void visitForStmt( AST::AstForStmt* , AST::ICollectInfoBack*) = 0;
        virtual void visitWhileStmt( AST::AstWhileStmt * , AST::ICollectInfoBack*) = 0;
        virtual void visitDoWhileStmt( AST::AstDoWhileStmt *, AST::ICollectInfoBack*) = 0;
        virtual void visitIfStmt( AST::AstIfStmt*, AST::ICollectInfoBack*) = 0;
        virtual void visitElseStmt( AST::AstElseStmt *, AST::ICollectInfoBack*) = 0;
        virtual void visitStmts( AST::AstStmts* , AST::ICollectInfoBack*) = 0;
        virtual void visitReturnStmt( AST::AstReturnStmt* , AST::ICollectInfoBack*) = 0;
        virtual void visitBreakStmt( AST::AstBreakStmt*  , AST::ICollectInfoBack*) = 0;
        virtual void visitContinueStmt( AST::AstContinueStmt* , AST::ICollectInfoBack*) = 0;
        virtual void visitExprStmt( AST::AstExprStmt*  , AST::ICollectInfoBack*) = 0;
        virtual void visitType(AST::AstType* , AST::ICollectInfoBack*) = 0;
        virtual void visitParamList(AST::AstParamList * , AST::ICollectInfoBack*) = 0;
        virtual void visitBlock(AST::AstBlock*, AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceBinaryOpExpr( AST::AstBinaryOpExpr* , AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceUnaryOpExpr(AST::AstUnaryOpExpr* , AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceConditionExpr( AST::AstConditionExpr*, AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceObjectExpr(AST::AstObjectExpr*, AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceConstantExpr(AST::AstConstantExpr*, AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceVoidExpr( AST::AstVoidExpr* , AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceDecl(AST::AstDecl*, AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceDecls(AST::AstDecls*, AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceAssign(AST::AstAssign*, AST::ICollectInfoBack*) = 0;
        virtual std::shared_ptr<AST::AstObjectExpr> reduceExprs(AST::AstExprs*, AST::ICollectInfoBack*) = 0;
    };

    class IASTModuleVisitor {
    
    };

    class IASTClassVisitor {


    };

    class IASTFunctionVisitor {


    };

    class IASTStmtVisitor {

    };

    class IASTExprVisitor {


    };

}