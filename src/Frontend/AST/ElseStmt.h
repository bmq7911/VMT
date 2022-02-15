#pragma once
#include "Frontend/AST/Stmt.h"

namespace AST {
    class ElseStmt : public std::enable_shared_from_this<ElseStmt>,public Stmt {
    public:
        ElseStmt(std::shared_ptr<AST::Stmt> elsestmts);
        std::shared_ptr<AST::Stmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor);
    private:

        std::shared_ptr<AST::Stmt>  m_stmt;
    };
}