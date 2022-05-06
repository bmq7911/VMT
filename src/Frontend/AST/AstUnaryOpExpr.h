#pragma once
#include "Frontend/AST/AstExpr.h"

namespace AST {
    // unarayExpr ::= op Expr
    class AstUnaryOpExpr : public AstExpr{
    public:
        AstUnaryOpExpr(std::shared_ptr<AST::AstExpr> expr, Token op);
        static std::shared_ptr<AST::AstUnaryOpExpr> makeUnaryOpExpr(std::shared_ptr<AST::AstExpr> expr, Token tok);
        std::shared_ptr<AST::AstExpr> getExpr() const;
        Token getOp() const;
        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        Token m_op;
        std::shared_ptr<AST::AstExpr> m_expr;
    };
}
