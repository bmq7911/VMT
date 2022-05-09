#pragma once
#include <iostream>
#include "Frontend/AST/AstVisitor.h"

class TestAstVisitor : public AST::IASTVisitor {
public:
	void visitProgram(AST::AstProgram*) override {
		std::cout <<"visitProgram" << std::endl;
	}
	// 这里存在一个问题就是作用域的问题
	void visitFunction(AST::AstFunction* function) override {
		std::cout << "visitFunction" << std::endl;
		Token functionName = function->getFunctionName( );
		std::cout << "function name: " << functionName.toStringView() << std::endl;
		std::shared_ptr<AST::AstType> type = function->getFunctionType( );
		
	}
	void visitForStmt(AST::AstForStmt*) override {
		std::cout << "visitForStmt" << std::endl;
	}
	void visitWhileStmt(AST::AstWhileStmt*) override {
		std::cout << "visitWhileStmt" << std::endl;
	}
	void visitDoWhileStmt(AST::AstDoWhileStmt*) override {
		std::cout << "visitDoWhileStmt" << std::endl;
	}
	void visitIfStmt(AST::AstIfStmt*) override {
		std::cout << "visitIfStmt" << std::endl;
	}
	void visitElseStmt(AST::AstElseStmt*) override {
		std::cout << "visitElseStmt" << std::endl;
	}
	void visitStmts(AST::AstStmts*) override {
		std::cout << "visitStmts" << std::endl;
	}
	void visitReturnStmt(AST::AstReturnStmt*) override {
		std::cout << "visitReturnStmt" << std::endl;
	}
	void visitBreakStmt(AST::AstBreakStmt*) override {
		std::cout << "visitBreakStmt" << std::endl;
	}
	void visitContinueStmt(AST::AstContinueStmt*) override {
		std::cout << "visitContinueStmt" << std::endl;
	}
	void visitExprStmt(AST::AstExprStmt*) override {
		std::cout << "visitForStmt" << std::endl;
	}

	std::shared_ptr<AST::AstObjectExpr> reduceBinaryOpExpr(AST::AstBinaryOpExpr*) override {
		std::cout << "reduceBinaryOpExpr" << std::endl;
		return nullptr;
	}
	std::shared_ptr<AST::AstObjectExpr> reduceUnaryOpExpr(AST::AstUnaryOpExpr*) override {
		std::cout << "reduceUnaryOpExpr" << std::endl;
		return nullptr;
	}
	std::shared_ptr<AST::AstObjectExpr> reduceConditionExpr(AST::AstConditionExpr*) override {
		std::cout << "reduceConditionExpr" << std::endl;
		return nullptr;
	}
	std::shared_ptr<AST::AstObjectExpr> reduceExprs(AST::AstExprs*) override {
		std::cout << "reduceExprs" << std::endl;
		return nullptr;
	}
	std::shared_ptr<AST::AstObjectExpr> reduceObjectExpr(AST::AstObjectExpr*) override {
		std::cout << "reduceObjectExpr" << std::endl;
		return nullptr;
	}
	std::shared_ptr<AST::AstObjectExpr> reduceVoidExpr(AST::AstVoidExpr*) override {
		std::cout << "reduceVoidExpr" << std::endl;
		return nullptr;
	}
	std::shared_ptr<AST::AstObjectExpr> reduceTemp(AST::AstTemp*) override {
		std::cout << "reduceTemp" << std::endl;
		return nullptr;
	}


};