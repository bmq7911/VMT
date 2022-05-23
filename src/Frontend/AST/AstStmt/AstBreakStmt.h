#pragma once
#include "Frontend/AST/AstStmt/AstStmt.h"
namespace AST {
    class AstBreakStmt :  public AstStmt {
    public:
        void gen(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack *) override;

    };
}