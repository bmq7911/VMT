#pragma once
#include "Frontend/AST/AstStmt.h"
#include "Frontend/AST/AstExpr.h"

namespace AST {

    class AstExprStmt :  public AstStmt {
    public:
        AstExprStmt(std::shared_ptr<AstExpr> & expr);
        std::shared_ptr<AST::AstExpr> getExpr();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::AstExpr> m_expr;
    };
}