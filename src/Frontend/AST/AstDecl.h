#pragma once
#include <vector>
#include "Frontend/AST/AstExpr.h"

namespace AST {
	class AstDecl : public AstExpr{
	public:
		std::shared_ptr<AST::AstObjectExpr> reduce( std::shared_ptr<AST::IASTVisitor> visitor );
	private:
		Token m_type;
		Token m_name;
		std::shared_ptr<AstExpr> m_expr;
	};
	class AstDecls : public AstExpr{
	public:
		std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor);
	private:
		std::vector<std::shared_ptr<AstDecl>> m_decls;
	};
}