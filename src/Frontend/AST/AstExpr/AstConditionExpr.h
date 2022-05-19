#pragma once
#include "Frontend/AST/AstExpr/AstExpr.h"
namespace AST {
    /// 类型操作还是不应该放到这个里面来做
    class IASTVisitor;
    class AstConditionExpr : public AstExpr {
    public:
        AstConditionExpr(std::shared_ptr<AST::AstExpr> condition, std::shared_ptr<AST::AstExpr> True, std::shared_ptr<AST::AstExpr> False);
        std::shared_ptr<AST::AstExpr> getCondition();
        std::shared_ptr<AST::AstExpr> getTrueExpr();
        std::shared_ptr<AST::AstExpr> getFalseExpr();
        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor>) override;
    private:
        std::shared_ptr<AST::AstExpr> m_condition;
        std::shared_ptr<AST::AstExpr> m_true;
        std::shared_ptr<AST::AstExpr> m_false;
    };
    
}