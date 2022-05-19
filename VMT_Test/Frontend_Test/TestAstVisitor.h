#pragma once
#include <iostream>
#include "Frontend/AST/AstVisitor.h"
#include "SymbolTable/Symbol.h"
#include "SymbolTable/Env.h"
#include "Diagnose/Diagnose.h"
#include "SymbolTable/ObjectId.h"
#include "SymbolTable/IntegerType.h"
#include "SymbolTable/RealType.h"
#include "SymbolTable/BoolType.h"

// 
class TestAstVisitor : public std::enable_shared_from_this<TestAstVisitor>, public AST::IASTVisitor {
public:
	TestAstVisitor() {
		m_topEnv = std::make_shared<ENV::Env>();
		std::shared_ptr<ENV::BoolType>              typeBool = std::make_shared<ENV::BoolType>(std::string_view("bool"));
		std::shared_ptr<ENV::IntegerType<int32_t>>  typeI32  = std::make_shared<ENV::IntegerType<int32_t>>( std::string_view("i32"), typeBool );
		std::shared_ptr<ENV::IntegerType<uint32_t>> typeUI32 = std::make_shared<ENV::IntegerType<uint32_t>>(std::string_view("ui32"), typeBool );
		std::shared_ptr<ENV::RealType<float>>       typeF32  = std::make_shared<ENV::RealType<float>>(std::string_view("f32"), typeBool );
		std::shared_ptr<ENV::RealType<double>>      typeF64  = std::make_shared<ENV::RealType<double>>(std::string_view("f64"), typeBool);
		m_topEnv->put(typeI32);
		m_topEnv->put(typeUI32);
		m_topEnv->put(typeF32);
		m_topEnv->put(typeF64);
		m_topEnv->put(typeBool);
		m_currentEnv = m_topEnv;
	}

	void visitProgram(AST::AstProgram* program ) override {
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
		body->gen( std::enable_shared_from_this<TestAstVisitor>::shared_from_this() );
	}

	void visitForStmt(AST::AstForStmt * forStmt ) override {
		std::cout << "visitForStmt" << std::endl;
	}

	void visitWhileStmt(AST::AstWhileStmt* whileStmt ) override {
		std::cout << "visitWhileStmt" << std::endl;
	}

	void visitDoWhileStmt(AST::AstDoWhileStmt* doWhileStmt ) override {
		std::cout << "visitDoWhileStmt" << std::endl;
	}

	void visitIfStmt(AST::AstIfStmt* ifStmt ) override {
		std::cout << "visitIfStmt" << std::endl;
	}

	void visitElseStmt(AST::AstElseStmt* elseStmt ) override {
		std::cout << "visitElseStmt" << std::endl;
	}

	void visitStmts(AST::AstStmts* stmts) override {
		std::cout << "visitStmts" << std::endl;
		for (size_t i = 0; i < stmts->size(); ++i) {
			stmts->at(i)->gen(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
		}
	}

	void visitReturnStmt(AST::AstReturnStmt* returnStmt ) override {
		std::cout << "visitReturnStmt" << std::endl;
	}

	void visitBreakStmt(AST::AstBreakStmt* breakStmt ) override {
		std::cout << "visitBreakStmt" << std::endl;
	}

	void visitContinueStmt(AST::AstContinueStmt* continueStmt ) override {
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
	std::shared_ptr<AST::AstObjectExpr> reduceUnaryOpExpr(AST::AstUnaryOpExpr* unaryOpExpr ) override {
		std::cout << "reduceUnaryOpExpr" << std::endl;
		return nullptr;
	}
	std::shared_ptr<AST::AstObjectExpr> reduceConditionExpr(AST::AstConditionExpr* conditionExpr ) override {
		std::cout << "reduceConditionExpr" << std::endl;
		return nullptr;
	}
	std::shared_ptr<AST::AstObjectExpr> reduceExprs(AST::AstExprs* exprs ) override {
		std::cout << "reduceExprs" << std::endl;
		return nullptr;
	}
	
	std::shared_ptr<AST::AstObjectExpr> reduceObjectExpr(AST::AstObjectExpr* objectExpr) override {
		std::cout << objectExpr->getObject().toStringView();
		return nullptr;
	}
	
	std::shared_ptr<AST::AstObjectExpr> reduceVoidExpr(AST::AstVoidExpr* voidExpr ) override {
		std::cout << "reduceVoidExpr" << std::endl;
		return nullptr;
	}

	std::shared_ptr<AST::AstObjectExpr> reduceTemp(AST::AstTemp* temp ) override {
		std::cout << "reduceTemp" << std::endl;
		return nullptr;
	}

	std::shared_ptr<AST::AstObjectExpr> reduceDecl(AST::AstDecl* decl) override {
		std::cout << "reduce Decl" << std::endl;
		auto env = getCurrentEnv();
		auto type = decl->getType();
		auto name = decl->getName();
		auto expr = decl->getExpr();
		auto ptype = env->find(type.toStringView(), ENV::SymbolType::kType);
		if (!ptype) {
			Diagnose::errorMsg( "can not find the type", type.toStringView() );
			return nullptr;
		}
		std::shared_ptr<ENV::Symbol> symbol = std::make_shared<ENV::ObjectId>( name.toStringView(), std::static_pointer_cast<ENV::TypeId>(ptype) );
		if (false == env->put(symbol)) {
			Diagnose::errorMsg("redefine the symbol", type.toStringView());
			return nullptr;
		}
		
		auto objExpr = expr->reduce( std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
		return objExpr;
	}

	std::shared_ptr<AST::AstObjectExpr> reduceDecls(AST::AstDecls* decls) override {
		auto iter = decls->begin();
		std::shared_ptr<AST::AstObjectExpr> objExpr;
		for (; iter != decls->end(); ++iter) {
			objExpr = (*iter)->reduce(std::enable_shared_from_this<TestAstVisitor>::shared_from_this());
		}
		return objExpr;
	}
	std::shared_ptr<AST::AstObjectExpr> reduceAssign(AST::AstAssign* assign ) override{
		std::cout << "reduce Assign" << std::endl;
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