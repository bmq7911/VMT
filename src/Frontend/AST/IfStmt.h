#pragma once
#include "Frontend/AST/Expr.h"
#include "Frontend/AST/Stmt.h"
#include "Frontend/AST/ElseStmt.h"

namespace AST {
    class IfStmt : public std::enable_shared_from_this<IfStmt>, public Stmt {
    public:
        IfStmt(std::shared_ptr<Expr> boolexpr,
            std::shared_ptr<AST::Stmt> ifstmt,
            std::shared_ptr<AST::ElseStmt> elsestmt);        /// 本质也是生成一种中间表示形式,且是四元式
        std::shared_ptr<AST::Expr> getBoolExpr();
        std::shared_ptr<AST::Stmt> getIfStmt();
        std::shared_ptr<AST::ElseStmt> getElseStmt();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::Expr> m_boolExpr;
        std::shared_ptr<AST::Stmt> m_stmt;
        std::shared_ptr<AST::ElseStmt> m_else;
    };
}