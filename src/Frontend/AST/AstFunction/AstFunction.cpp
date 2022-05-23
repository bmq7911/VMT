#include "Frontend/AST/AstFunction/AstFunction.h"
#include "Frontend/AST/AstVisitor.h"

namespace AST {

    Token AstFunction::getFunctionName() const {
        return m_funName;
    }
    std::shared_ptr<AST::AstType> AstFunction::getFunctionType() const {
        return m_type;
    }

    std::shared_ptr<AST::AstParamList> AstFunction::getFunctionParamList() const {
        return m_paramList;
    }
    std::shared_ptr<AST::AstAttribute> AstFunction::getFunctionAttribute() const {
        return m_attribute;
    }
    std::shared_ptr<AST::AstBlock>     AstFunction::getFunctionBlock() const {
        return m_functionBody;
    }

	void AstFunction::gen( std::shared_ptr<AST::IASTVisitor> visitor, ICollectInfoBack * collect) {
		visitor->visitFunction(this, collect );
	}
}
