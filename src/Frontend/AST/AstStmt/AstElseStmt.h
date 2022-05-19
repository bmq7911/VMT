#pragma once
#include "Frontend/AST/AstStmt/AstStmt.h"

namespace AST {
    class AstElseStmt : public AstStmt {
    public:
        AstElseStmt(std::shared_ptr<AST::AstStmt> elsestmts);
        std::shared_ptr<AST::AstStmt> getStmt();
        void gen(std::shared_ptr<AST::IASTVisitor> visitor);
    private:

        std::shared_ptr<AST::AstStmt>  m_stmt;
    };
}