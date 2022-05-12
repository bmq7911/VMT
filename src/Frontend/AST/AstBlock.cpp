#include "Frontend/AST/AstBlock.h"
#include "Frontend/AST/AstVisitor.h"

namespace AST {
	void AstBlock::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
		visitor->visitBlock( this );
	}
}