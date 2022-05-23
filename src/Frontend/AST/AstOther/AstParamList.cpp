#include "Frontend/AST/AstOther/AstParamList.h"
#include "Frontend/AST/AstVisitor.h"
namespace AST {
	void AstParamList::gen(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack * collect) {
		visitor->visitParamList(this, collect);
	}

}