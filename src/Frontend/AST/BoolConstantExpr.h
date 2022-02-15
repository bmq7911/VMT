#pragma once
#include "Frontend/AST/ConstantExpr.h"
#include <string>
namespace AST {
    class IASTVisitor;
    class BoolConstantExpr : public std::enable_shared_from_this<BoolConstantExpr>, public ConstantExpr<bool> {
    public:
        BoolConstantExpr(std::shared_ptr<ENV::TypeId> id, Token tok, typename ConstantExpr::HostType value);
        std::shared_ptr<AST::ObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor>) override;
        std::string toString() const;
    private:
        const char * m_value;
    };
}