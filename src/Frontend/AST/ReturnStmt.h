#pragma once
#include "Frontend/AST/ExprStmt.h"
#include "Frontend/AST/Stmt.h"
namespace AST {
    class ReturnStmt : public std::enable_shared_from_this<ReturnStmt>, public Stmt {
    public:
        ReturnStmt(std::shared_ptr<AST::ExprStmt> stmt);
        std::shared_ptr<AST::ExprStmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor>) override;
    private:
        std::shared_ptr<AST::ExprStmt> m_returnExprStmt;
    };
}