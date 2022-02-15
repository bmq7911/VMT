#pragma once
#include "Frontend/AST/Expr.h"
namespace AST {
	class VoidExpr : public std::enable_shared_from_this<VoidExpr>, public Expr {
	public:
        std::shared_ptr<AST::ObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor) override;
    
	};
}