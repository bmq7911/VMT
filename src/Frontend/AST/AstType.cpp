#include "Frontend/AST/AstType.h"
#include "Frontend/AST/AstVisitor.h"
namespace AST{
	void AstType::gen( std::shared_ptr<AST::IASTVisitor> visitor){
		visitor->visitType( this );
	}

}
