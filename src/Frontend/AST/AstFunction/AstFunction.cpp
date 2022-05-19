#include "Frontend/AST/AstFunction/AstFunction.h"
#include "Frontend/AST/AstVisitor.h"

namespace AST {

    Token AstFunction::getFunctionName() const {
        return m_funName;
    }
    std::shared_ptr<AST::AstType> AstFunction::getFunctionType() const {
        return m_type;
    }


	void AstFunction::gen( std::shared_ptr<AST::IASTVisitor> visitor) {
		visitor->visitFunction(this);
	}
}
