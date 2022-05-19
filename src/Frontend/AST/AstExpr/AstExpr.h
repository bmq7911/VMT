#pragma once
#include <string>
#include "Frontend/AST/AstTree.h"
#include "Frontend/Lexer/Token.h"
#include "SymbolTable/TypeId.h"

namespace AST {
    ///
    class IASTVisitor;
    class AstObjectExpr;

    class AstExpr : public AstTree {
    public:
        AstExpr() {}
        virtual std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor) = 0;
    private:
    };
}
