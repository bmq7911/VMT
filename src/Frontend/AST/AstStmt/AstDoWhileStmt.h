#pragma once
#include "Frontend/AST/AstStmt/AstLoopStmt.h"
#include "Frontend/AST/AstExpr/AstExpr.h"

namespace AST {
    class AstDoWhileStmt : public AstLoopStmt {
    public:
        AstDoWhileStmt(std::shared_ptr<AST::AstExpr> expr, std::shared_ptr<AST::AstStmt> stmt);
        std::shared_ptr<AST::AstStmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::AstStmt> m_stmt;
    };
    
}