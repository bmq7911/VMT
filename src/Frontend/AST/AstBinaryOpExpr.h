#pragma once
#include "Frontend/AST/AstExpr.h"
#include "Frontend/AST/AstTemp.h"

namespace AST {
    class IASTVisitor;
    class AstBinaryOpExpr : public AstExpr{
    public:
        AstBinaryOpExpr(std::shared_ptr<AstExpr> left,
            std::shared_ptr<AstExpr> right,
            Token tok);
        static std::shared_ptr<AstBinaryOpExpr> makeBinaryOpExpr(std::shared_ptr<AstExpr> left, std::shared_ptr<AstExpr> right, Token tok);
        std::shared_ptr<AstExpr> getLeft() const;
        std::shared_ptr<AstExpr> getRight() const;
        Token getOp() const;

        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor>) override;

    private:
        std::shared_ptr<AstExpr> m_left;
        std::shared_ptr<AstExpr> m_right;
        Token                 m_op;
    };

}