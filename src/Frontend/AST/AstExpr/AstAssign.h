#pragma once
#include <memory>
#include "Frontend/AST/AstExpr/AstExpr.h"
namespace AST {
	class AstAssign : public AstExpr {
	public:
		AstAssign(Token tok, std::shared_ptr<AstExpr> expr)
			: m_tok( tok )
			, m_expr( expr )
		{
		}
		Token getToken() const {
			return m_tok;
		}
		std::shared_ptr<AstExpr> getExpr() {
			return m_expr;
		}
        std::shared_ptr<AST::AstObjectExpr> reduce(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack* ) override;
	private:
		Token m_tok;
		std::shared_ptr<AstExpr> m_expr;
	};


}
