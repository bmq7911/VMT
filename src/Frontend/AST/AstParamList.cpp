#include "Frontend/AST/AstParamList.h"
#include "Frontend/AST/AstVisitor.h"
namespace AST {
	void AstParamList::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
		visitor->visitParamList(this);
	}

}