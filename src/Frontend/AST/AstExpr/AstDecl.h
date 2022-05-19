#pragma once
#include <vector>
#include "Frontend/AST/AstExpr/AstExpr.h"

namespace AST {
	class AstDecl : public AstExpr{
	public:
		AstDecl(Token type, Token name, std::shared_ptr<AstExpr> expr);
		Token getType() const;
		Token getName() const;
		std::shared_ptr<AstExpr> getExpr() const;
		std::shared_ptr<AST::AstObjectExpr> reduce( std::shared_ptr<AST::IASTVisitor> visitor );
	private:
		Token m_type;
		Token m_name;
		std::shared_ptr<AstExpr> m_expr;
	};
	class AstDecls : public AstExpr{
	public:
		using iterator = std::vector<std::shared_ptr<AstDecl>>::iterator;
		void push(std::shared_ptr<AST::AstDecl>);
		iterator begin();
		iterator end();
		std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor);
	private:
		std::vector<std::shared_ptr<AstDecl>> m_decls;
	};
}