#pragma once
#include "Frontend/AST/Stmt.h"
#include "Frontend/AST/Expr.h"

namespace AST {
    class LoopStmt : public Stmt {
    public:
        LoopStmt(std::shared_ptr<AST::Expr> expr) 
            : m_loopExpr(expr)
        {}
        std::shared_ptr<Expr>& getLoopExpr() {
            return m_loopExpr;
        }
    private:
        std::shared_ptr<Expr> m_loopExpr;
    };



}