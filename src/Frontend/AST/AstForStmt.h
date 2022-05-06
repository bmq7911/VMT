#pragma once
#include "Frontend/AST/AstLoopStmt.h"
#include "Frontend/AST/AstExpr.h"

namespace AST {
    class IASTVisitor;
    class AstForStmt : public AstLoopStmt {
    public:
        
        AstForStmt(std::shared_ptr<AST::AstExpr> initExpr, std::shared_ptr<AST::AstExpr> boolExpr,
            std::shared_ptr<AST::AstExpr> tailExpr, std::shared_ptr<AST::AstStmt> stmt);
        std::shared_ptr<AST::AstExpr> getInitExpr();
        std::shared_ptr<AST::AstExpr> getTailExpr();
        std::shared_ptr<AST::AstStmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::AstExpr> m_initExpr;
        std::shared_ptr<AST::AstExpr> m_tailExpr;
        std::shared_ptr<AST::AstStmt> m_stmt;

    };
}