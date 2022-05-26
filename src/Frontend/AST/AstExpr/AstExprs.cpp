#include "Frontend/AST/AstExpr/AstExprs.h"
#include "Frontend/AST/AstExpr/AstObjectExpr.h"

#include "Frontend/AST/AstVisitor.h"
namespace AST{
	
	std::shared_ptr<AST::AstObjectExpr> AstExprs::reduce( std::shared_ptr<AST::IASTVisitor> visitor, ICollectInfoBack * collect ){
		return visitor->reduceExprs( this ,collect );
	}
	
}