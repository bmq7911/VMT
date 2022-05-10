#pragma once
#include "Frontend/AST/AstFunctionBody.h"
#include "Frontend/AST/AstVisitor.h"

namespace AST {
	std::shared_ptr<AstParamList> AstFunctionBody::getParamList() const {
		return m_paramList;
	}
	std::shared_ptr<AstStmt>      AstFunctionBody::getStmt() const {
		return m_stmt;
	}	
	void AstFunctionBody::gen(std::shared_ptr<AST::IASTVisitor> visitor) {
		visitor->visitFunctionBody( this );
	}
}