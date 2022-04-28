#pragma once 
#include "Frontend/AST/Node.h"
#include "Frontend/Lexer/Token.h"

namespace AST {
	class IASTVisitor;
	class Type : public Node {
	public:
		Type( Token tok)
			: m_tok( tok )
		{

		}
		void gen(std::shared_ptr<AST::IASTVisitor> visitor) {
		}
	private:
		Token m_tok;
	};
}