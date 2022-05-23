#pragma once
#include "Frontend/AST/AstStmt/AstExprStmt.h"
#include "Frontend/AST/AstStmt/AstStmt.h"
namespace AST {
    class AstReturnStmt : public AstStmt {
    public:
        AstReturnStmt(std::shared_ptr<AST::AstExprStmt> stmt);
        std::shared_ptr<AST::AstExprStmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor>,ICollectInfoBack* ) override;
    private:
        std::shared_ptr<AST::AstExprStmt> m_returnExprStmt;
    };
}