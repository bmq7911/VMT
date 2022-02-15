#pragma once
#include "Frontend/AST/Stmt.h"
namespace AST {
    class Stmts : public std::enable_shared_from_this<Stmts>, public Stmt {
    public:
        void add(std::shared_ptr<AST::Stmt> stmt);
        size_t size() const;
        std::shared_ptr<AST::Stmt> at(size_t index);
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;
    private:
        std::vector<std::shared_ptr<AST::Stmt>> m_stmts;
    };
}