#include "Frontend/AST/AstExpr/AstExprs.h"
#include "Frontend/AST/AstVisitor.h"
namespace AST {
	std::shared_ptr<AST::AstObjectExpr> AstObjectExpr::reduce(std::shared_ptr<AST::IASTVisitor> visitor, ICollectInfoBack* collect) {
		return visitor->reduceObjectExpr(this, collect);
	}
}
