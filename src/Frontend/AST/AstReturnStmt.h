#pragma once
#include "Frontend/AST/AstExprStmt.h"
#include "Frontend/AST/AstStmt.h"
namespace AST {
    class AstReturnStmt : public AstStmt {
    public:
        AstReturnStmt(std::shared_ptr<AST::AstExprStmt> stmt);
        std::shared_ptr<AST::AstExprStmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor>) override;
    private:
        std::shared_ptr<AST::AstExprStmt> m_returnExprStmt;
    };
}