#pragma once
#include "Frontend/AST/Node.h"
#include "Frontend/Lexer/Token.h"

namespace AST{
	class IASTVisitor;
	class Attribute : public Node{
	public:
		Attribute( Token tok)
			: m_tok( tok )
		{
		}
		//virtual void gen(std::shared_ptr<AST::IASTVisitor> visitor) = 0;
	private:
		Token m_tok;
	};
	
}