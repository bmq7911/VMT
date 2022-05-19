#pragma once
#include "Frontend/AST/AstExpr/AstExpr.h"
#include "Frontend/AST/AstStmt/AstStmt.h"
#include "Frontend/AST/AstStmt/AstElseStmt.h"

namespace AST {
    class AstIfStmt : public AstStmt {
    public:
        AstIfStmt(std::shared_ptr<AstExpr> boolexpr,
            std::shared_ptr<AST::AstStmt> ifstmt,
            std::shared_ptr<AST::AstElseStmt> elsestmt);        /// ����Ҳ������һ���м��ʾ��ʽ,������Ԫʽ
        std::shared_ptr<AST::AstExpr> getBoolExpr();
        std::shared_ptr<AST::AstStmt> getIfStmt();
        std::shared_ptr<AST::AstElseStmt> getElseStmt();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::shared_ptr<AST::AstExpr> m_boolExpr;
        std::shared_ptr<AST::AstStmt> m_stmt;
        std::shared_ptr<AST::AstElseStmt> m_else;
    };
}