#pragma once
#include <vector>
#include "Frontend/AST/AstStmt/AstStmt.h"
namespace AST {
	class AstBlock :public AstStmt {
	public:
		void gen(std::shared_ptr<AST::IASTVisitor> visitor,ICollectInfoBack* )  override;
		void addStmt(std::shared_ptr<AST::AstStmt> stmt) {
			m_stmts.push_back(stmt);
		}
		using iterator = std::vector<std::shared_ptr<AST::AstStmt>>::iterator;
		iterator begin() {
			return m_stmts.begin();
		}
		iterator end() {
			return m_stmts.end();
		}
	private:
		std::vector<std::shared_ptr<AST::AstStmt>> m_stmts;
	};
}