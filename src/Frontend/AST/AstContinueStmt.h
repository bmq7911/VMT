#pragma once
#include "Frontend/AST/AstStmt.h"
namespace AST {
    class AstContinueStmt : public AstStmt {
    public:
        void gen(std::shared_ptr<AST::IASTVisitor> visitor) override;

    };
}
