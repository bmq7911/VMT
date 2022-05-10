#pragma once
#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstParamList.h"
#include "Frontend/AST/AstStmt.h"
namespace AST{
    class IASTVisitor;
    class AstFunctionBody : public AstTree{
    public:
        AstFunctionBody( std::shared_ptr<AstParamList> paramList, std::shared_ptr<AstStmt> stmt ) 
            : m_paramList( paramList )
            , m_stmt( stmt )
        {

        }
        std::shared_ptr<AstParamList> getParamList() const;
        std::shared_ptr<AstStmt>      getStmt() const;
        void gen(std::shared_ptr<AST::IASTVisitor>);
    private:
        std::shared_ptr<AstParamList> m_paramList;
        std::shared_ptr<AstStmt> m_stmt;
    };

}