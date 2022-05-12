#pragma once
#include <iostream>
#include "Frontend/AST/AstVisitor.h"
#include "SymbolTable/Symbol.h"
#include "SymbolTable/Env.h"

// 

class TestAstVisitor : public std::enable_shared_from_this<TestAstVisitor>, public AST::IASTVisitor {
public:
	TestAstVisitor() {
		m_topEnv = std::make_shared<ENV::Env>();
		m_currentEnv = m_topEnv;
	}
	void visitProgram(AST::AstProgram*) override {
		std::cout <<"visitProgram" << std::endl;
	}
	// 这里存在一个问题就是作用域的问题
	void visitFunction(AST::AstFunction* function) override {
		std::cout << "visitFunction" << std::endl;
		Token functionName = function->getFunctionName( );
		std::cout << "function name: " << functionName.toStringView() << std::endl;
		std::shared_ptr<AST::AstType> type = function->getFunctionType( );
		type->gen( std::enable_shared_from_this<TestAstVisitor>::shared_from_this() );
		std::shared_ptr<AST::AstFunctionBody> body = function->getFunctionBody();
		body->gen(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
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
	void visitStmts(AST::AstStmts* stmts) override {
		std::cout << "visitStmts" << std::endl;
		for (size_t i = 0; i < stmts->size(); ++i) {
			stmts->at(i)->gen(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
		}
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
	void visitExprStmt(AST::AstExprStmt* exprStmt) override {
		std::cout << "visitExprStmt" << std::endl;
		exprStmt->getExpr()->reduce(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
	}

	void visitBlock(AST::AstBlock* block) override {
		std::shared_ptr<ENV::Env> env = std::make_shared<ENV::Env>( getCurrentEnv() );
		env->mount(getCurrentEnv());
			_VisitBlock( block );
		env->unmount( );
	}
	void _VisitBlock(AST::AstBlock* block) {
		std::shared_ptr<ENV::Env> env = getCurrentEnv();
		for (auto iter = block->begin(); iter != block->end(); ++iter) {
			(*iter)->gen(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
		}
		std::cout << "visitBlock" << std::endl;

	}
	void visitType(AST::AstType* type) override {
		std::cout << "Type: "<< type->getType().toStringView() << std::endl;
	}
	void visitFunctionBody(AST::AstFunctionBody* body) override {
		std::cout << "FunctionBody:" << std::endl;
		body->getParamList()->gen(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
		body->getStmt()->gen(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
	}
	void visitParamList(AST::AstParamList * list) override {
		std::cout << "ParamList size " << list->size() << std::endl;
		for (size_t i = 0; i < list->size(); ++i) {
			AST::AstParam &param = list->at(i);
			std::cout << "\t" << param.getType().toStringView() << " " << param.getId().toStringView() <<std::endl;
		}
	}
	std::shared_ptr<AST::AstObjectExpr> reduceBinaryOpExpr(AST::AstBinaryOpExpr* binaryOpExpr) override {
		//std::cout << "reduceBinaryOpExpr" << std::endl;
		auto leftExpr = binaryOpExpr->getLeft();
		auto rightExpr = binaryOpExpr->getRight();
		leftExpr->reduce(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
		std::cout << binaryOpExpr->getOp().toStringView();
		rightExpr->reduce(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
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
	std::shared_ptr<AST::AstObjectExpr> reduceObjectExpr(AST::AstObjectExpr* objectExpr) override {
		std::cout << objectExpr->getObject().toStringView();
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
private:
	std::shared_ptr<ENV::Env> getCurrentEnv() {
		return m_currentEnv;
	}

private:
	std::shared_ptr<ENV::Env>  m_topEnv;
	std::shared_ptr<ENV::Env>  m_currentEnv;
};