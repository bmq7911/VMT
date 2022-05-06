#pragma once
#include "Frontend/AST/AstTree.h"
#include "Frontend/Lexer/Token.h"

namespace AST{
	class IASTVisitor;
	class AstAttribute : public AstTree{
	public:
		AstAttribute( Token tok)
			: m_tok( tok )
		{
		}
	private:
		Token m_tok;
	};
	
}