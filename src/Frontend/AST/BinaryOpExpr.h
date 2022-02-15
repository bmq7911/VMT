#pragma once
#include "Frontend/AST/Expr.h"
#include "Frontend/AST/Temp.h"

namespace AST {
    class IASTVisitor;
    class BinaryOpExpr : public std::enable_shared_from_this<BinaryOpExpr>, public Expr{
    public:
        BinaryOpExpr(std::shared_ptr<Expr> left,
            std::shared_ptr<Expr> right,
            Token tok,
            std::shared_ptr<ENV::TypeId> type);
        static std::shared_ptr<BinaryOpExpr> makeBinaryOpExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right, Token tok);
        std::shared_ptr<Expr> getLeft() const;

        std::shared_ptr<Expr> getRight() const;

        Token getOp() const;

        std::shared_ptr<AST::ObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor>) override;

    private:
        std::shared_ptr<Expr> m_left;
        std::shared_ptr<Expr> m_right;
        Token                 m_op;
    };

}