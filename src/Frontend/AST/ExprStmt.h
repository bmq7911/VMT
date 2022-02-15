#pragma once
#include "Frontend/AST/Stmt.h"
#include "Frontend/AST/Expr.h"

namespace AST {

    class ExprStmt : public std::enable_shared_from_this<ExprStmt>, public Stmt {
    public:
        ExprStmt(std::shared_ptr<Expr> & expr);
        std::shared_ptr<AST::Expr> getExpr();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::Expr> m_expr;
    };
}