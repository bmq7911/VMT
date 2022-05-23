#pragma once
#include <memory>
#include "Frontend/AST/AstTree.h"
namespace AST {
    class IASTVisitor;
    class ICollectInfoBack;
    class AstStmt :  public AstTree{
    public:
        AstStmt() { }
        static AstStmt * Null;
        virtual void gen(std::shared_ptr<AST::IASTVisitor> visitor, ICollectInfoBack * collect ) = 0;
        int m_after = 0;                   
        static AstStmt* Enclosing;

    };
}
