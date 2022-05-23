#pragma once
#include "Frontend/AST/AstExpr/AstExpr.h"
#include "Frontend/AST/AstExpr/AstTemp.h"

namespace AST {
    class IASTVisitor;
    class ICollectInfoBack;
    class AstBinaryOpExpr : public AstExpr{
    public:
        AstBinaryOpExpr(std::shared_ptr<AstExpr> left,
            std::shared_ptr<AstExpr> right,
            Token tok);
        static std::shared_ptr<AstBinaryOpExpr> makeBinaryOpExpr(std::shared_ptr<AstExpr> left, std::shared_ptr<AstExpr> right, Token tok);
        std::shared_ptr<AstExpr> getLeft() const;
        std::shared_ptr<AstExpr> getRight() const;
        Token getOp() const;

        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor>, ICollectInfoBack * collect) override;

    private:
        std::shared_ptr<AstExpr> m_left;
        std::shared_ptr<AstExpr> m_right;
        Token                 m_op;
    };

}