#pragma once
#include <vector>
#include "Frontend/AST/AstExpr.h"
namespace AST {
    class IASTVisitor;
    class AstExprs :public AstExpr {
    public:
        void add(std::shared_ptr<AST::AstExpr> expr);
        size_t size() const;
        std::shared_ptr<AST::AstExpr> at(uint32_t i) const;
        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor) override;
        
    private:
        std::vector<std::shared_ptr<AST::AstExpr>> m_exprs;
    };

}