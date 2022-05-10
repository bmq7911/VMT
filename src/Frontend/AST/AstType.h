#pragma once 
#include <memory>
#include "Frontend/AST/AstTree.h"
#include "Frontend/Lexer/Token.h"

namespace AST {
	class IASTVisitor;
	class AstType : public AstTree {
	public:
		AstType( Token tok)
			: m_tok( tok )
		{

		}
		Token getType() const {
			return m_tok;
		}
		void gen(std::shared_ptr<AST::IASTVisitor> visitor);
	private:
		Token m_tok;
	};
}