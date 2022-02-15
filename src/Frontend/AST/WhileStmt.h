#pragma once
#include "Frontend/AST/LoopStmt.h"
#include "Frontend/AST/Expr.h"

namespace AST {

    class WhileStmt : public std::enable_shared_from_this<WhileStmt>,public LoopStmt {
    public:
        WhileStmt(std::shared_ptr<AST::Expr> expr, std::shared_ptr<AST::Stmt> stmt);
        std::shared_ptr<AST::Stmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::Stmt> m_stmt;
    };
    
}