#include "Frontend/AST/AstExpr/AstDecl.h"
#include "Frontend/AST/AstVisitor.h"
namespace AST {

	AstDecl::AstDecl(Token type, Token name, std::shared_ptr<AstExpr> expr)
		: m_type( type )
		, m_name( name )
		, m_expr( expr )
	{
	}
	Token AstDecl::getType() const {
		return m_type;
	}
	Token AstDecl::getName() const {
		return m_name;
	}
	std::shared_ptr<AstExpr> AstDecl::getExpr() const {
		return m_expr;
	}

	std::shared_ptr<AST::AstObjectExpr> AstDecl::reduce(std::shared_ptr<AST::IASTVisitor> visitor) {
		return visitor->reduceDecl( this );
	}

	void AstDecls::push(std::shared_ptr<AST::AstDecl> decl) {
		m_decls.push_back(decl);
	}
	AstDecls::iterator AstDecls::begin() {
		return m_decls.begin( );
	}

	AstDecls::iterator AstDecls::end() {
		return m_decls.end( );
	}

	std::shared_ptr<AST::AstObjectExpr> AstDecls::reduce(std::shared_ptr<AST::IASTVisitor> visitor) {
		return visitor->reduceDecls( this);
	}
}
