#pragma once
#include <vector>
#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstObjectExpr.h"
#include "Frontend/AST/AstStmt.h"
#include "Frontend/AST/AstType.h"
#include "Frontend/AST/AstAttribute.h"
#include "Frontend/AST/AstFunctionBody.h"
#include "Frontend/AST/AstParamList.h"
#include "SymbolTable/TypeId.h"
#include "SymbolTable/FunctionId.h"


namespace AST {

    class AstFunction :  public  AstTree{
    public:
        void init(std::shared_ptr<ENV::TypeId>  type,
                  Token name,
                  std::shared_ptr<AST::AstStmt> stmt,
                  std::shared_ptr<AST::AstParamList> param,
                  std::shared_ptr<ENV::Env> env) 
        {
            m_type    = type;
            m_funName = name;
            m_args    = param;
            m_functionEnv = env;
            m_stmts       = stmt;
        }
        std::string getFunctionName() const{
            return m_funName.toString();
        }
        std::shared_ptr<AST::AstParamList> getParamList() {
            return m_args;
        }
        std::shared_ptr<AST::AstStmt>      getStmt() {
            return m_stmts;
        }
    private:
        std::shared_ptr<ENV::TypeId>     m_type;
        Token                            m_funName;
        std::shared_ptr<AST::AstParamList>       m_args;
        std::shared_ptr<AST::AstStmt>       m_stmts;

        std::shared_ptr<ENV::Env>        m_functionEnv; 
        std::shared_ptr<ENV::FunctionId> m_functionInfo;
        std::shared_ptr<AST::AstType>       m_returnType;
        std::shared_ptr<AST::AstAttribute>  m_attribute;
        std::shared_ptr<AST::AstFunctionBody> m_functionBody;
    };
}