#pragma once
#include <string_view>
#include <vector>
#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstExpr/AstExpr.h"
namespace AST {
	class IASTVisitor;
	class ICollectInfoBack;
	class AstObjectExpr;
	class AstExprs : public AstExpr{
	public:
		using iterator = std::vector<std::shared_ptr<AstExpr>>::iterator;
		AstExprs() {}
		void add(std::shared_ptr<AST::AstExpr> expr) {
			m_exprs.push_back(expr);
		}
		iterator begin() {
			return m_exprs.begin();
		}
		iterator end() {
			return m_exprs.end( );
		}
		std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor, ICollectInfoBack* collect) override;
	private:
		std::vector<std::shared_ptr<AstExpr>> m_exprs;
	};
}