#pragma once
#include "Frontend/AST/AstStmt.h"
namespace AST {
    class AstStmts : public AstStmt {
    public:
        void add(std::shared_ptr<AST::AstStmt> stmt);
        size_t size() const;
        std::shared_ptr<AST::AstStmt> at(size_t index);
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::vector<std::shared_ptr<AST::AstStmt>> m_stmts;
    };
}