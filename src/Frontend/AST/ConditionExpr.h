#pragma once
#include "Frontend/AST/Expr.h"
namespace AST {
    /// 类型操作还是不应该放到这个里面来做
    class IASTVisitor;
    class ConditionExpr : public std::enable_shared_from_this<ConditionExpr> ,public Expr {
    public:
        ConditionExpr(std::shared_ptr<AST::Expr> condition, std::shared_ptr<AST::Expr> True, std::shared_ptr<AST::Expr> False);
        std::shared_ptr<AST::Expr> getCondition();
        std::shared_ptr<AST::Expr> getTrueExpr();
        std::shared_ptr<AST::Expr> getFalseExpr();
        std::shared_ptr<AST::ObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor>) override;
    private:
        std::shared_ptr<AST::Expr> m_condition;
        std::shared_ptr<AST::Expr> m_true;
        std::shared_ptr<AST::Expr> m_false;
    };
    
}