#pragma once
#include "Frontend/AST/LoopStmt.h"
#include "Frontend/AST/Expr.h"

namespace AST {
    class IASTVisitor;
    class ForStmt : public std::enable_shared_from_this<ForStmt>,public LoopStmt {
    public:
        
        ForStmt(std::shared_ptr<AST::Expr> initExpr, std::shared_ptr<AST::Expr> boolExpr,
            std::shared_ptr<AST::Expr> tailExpr, std::shared_ptr<AST::Stmt> stmt);
        std::shared_ptr<AST::Expr> getInitExpr();
        std::shared_ptr<AST::Expr> getTailExpr();
        std::shared_ptr<AST::Stmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::Expr> m_initExpr;
        std::shared_ptr<AST::Expr> m_tailExpr;
        std::shared_ptr<AST::Stmt> m_stmt;

    };
}