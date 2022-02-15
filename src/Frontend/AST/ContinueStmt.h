#pragma once
#include "Frontend/AST/Stmt.h"
namespace AST {
    class ContinueStmt :  public std::enable_shared_from_this<ContinueStmt>,public Stmt {
    public:
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;

    };
}
