#include "Frontend/AST/AstExpr/AstAssign.h"
#include "Frontend/AST/AstVisitor.h"
namespace AST {
	std::shared_ptr<AST::AstObjectExpr> AstAssign::reduce( std::shared_ptr<AST::IASTVisitor> visitor ,ICollectInfoBack * collect) {
		return visitor->reduceAssign( this, collect);
	}
}
