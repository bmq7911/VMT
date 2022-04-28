#pragma once 

#include "Frontend/AST/Node.h"

namespace AST {
	class IASTVisitor;
	class Type : public Node {
	public:
		void gen(std::shared_ptr<AST::IASTVisitor> visitor) {
		}
	private:

	};
}