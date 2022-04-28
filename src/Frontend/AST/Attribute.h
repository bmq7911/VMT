#pragma once
#include "Frontend/AST/Node.h"

namespace AST{
	class IASTVisitor;
	class Attribute : public Node{
	public:
		virtual void gen(std::shared_ptr<AST::IASTVisitor> visitor) = 0;
		
	};
	
}