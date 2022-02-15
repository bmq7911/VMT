#pragma once
#include "Frontend/AST/Expr.h"
namespace AST {
    class IASTVisitor;
    class Exprs :public std::enable_shared_from_this<Exprs>, public Expr {
    public:
        void add(std::shared_ptr<AST::Expr> expr);
        size_t size() const;
        std::shared_ptr<AST::Expr> at(uint32_t i) const;
        std::shared_ptr<AST::ObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor) override;
        
    private:
        std::vector<std::shared_ptr<AST::Expr>> m_exprs;
    };

}