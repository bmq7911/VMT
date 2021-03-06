#pragma once
#include "Frontend/AST/AstExpr/AstExpr.h"
namespace AST {
	class AstVoidExpr : public AstExpr {
	public:
        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack *) override;
    
	};
}