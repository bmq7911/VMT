#pragma once
#include "Frontend/AST/Expr.h"

namespace AST {
    /// ∂‡÷ÿºÃ≥–
    class UnaryOpExpr : public std::enable_shared_from_this<UnaryOpExpr>, public Expr{
    public:
        UnaryOpExpr(std::shared_ptr<AST::Expr> expr, Token tok, std::shared_ptr<ENV::TypeId> type);
        static std::shared_ptr<UnaryOpExpr> makeUnaryOpExpr(std::shared_ptr<AST::Expr> expr, Token tok);
        std::shared_ptr<AST::Expr> getExpr() const;
        Token getOp() const;
        std::shared_ptr<AST::ObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::Expr> m_expr;
        Token m_op;
    };
}
