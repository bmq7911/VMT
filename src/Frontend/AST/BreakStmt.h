#pragma once
#include "Frontend/AST/Stmt.h"
namespace AST {
    class BreakStmt :  public std::enable_shared_from_this<BreakStmt>,public Stmt {
    public:
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;

    };
}