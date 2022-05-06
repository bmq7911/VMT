#pragma once
#include "Frontend/AST/AstLoopStmt.h"
#include "Frontend/AST/AstExpr.h"

namespace AST {

    class AstWhileStmt : public AstLoopStmt {
    public:
        AstWhileStmt(std::shared_ptr<AST::AstExpr> expr, std::shared_ptr<AST::AstStmt> stmt);
        std::shared_ptr<AST::AstStmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::AstStmt> m_stmt;
    };
    
}