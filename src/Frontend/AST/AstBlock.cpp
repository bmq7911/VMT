#include "Frontend/AST/AstBlock.h"
#include "Frontend/AST/AstVisitor.h"

namespace AST {
	void AstBlock::gen(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack * collect ) {
		visitor->visitBlock( this , collect );
	}
}