#pragma once
#include "Frontend/AST/AstConstantExpr.h"
#include <string>
namespace AST {
    class IASTVisitor;
    class AstBoolConstantExpr :  public AstConstantExpr<bool> {
    public:
        AstBoolConstantExpr(std::shared_ptr<ENV::TypeId> id, Token tok, typename AstConstantExpr::HostType value);
        std::string toString() const;
    private:
        const char * m_value;
    };
}