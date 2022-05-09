#pragma once
#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstParamList.h"
#include "Frontend/AST/AstStmt.h"
namespace AST{
    class AstFunctionBody : public AstTree{
    public:
        AstFunctionBody( std::shared_ptr<AstParamList> paramList, std::shared_ptr<AstStmt> stmt ) 
            : m_paramList( paramList )
            , m_stmt( stmt )
        {

        }
    private:
        std::shared_ptr<AstParamList> m_paramList;
        std::shared_ptr<AstStmt> m_stmt;
    };

}