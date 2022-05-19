#pragma once
#include <vector>
#include <memory>

#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstExpr/AstObjectExpr.h"
#include "Frontend/AST/AstStmt/AstStmt.h"
#include "Frontend/AST/AstOther/AstType.h"
#include "Frontend/AST/AstOther/AstAttribute.h"
#include "Frontend/AST/AstOther/AstParamList.h"


namespace AST {
    
    class AstFunction :  public  AstTree{
    public:
        AstFunction( Token name, std::shared_ptr<AstType> type) 
            : m_funName( name)
            , m_type( type )
        {
        }

        Token getFunctionName() const;
        std::shared_ptr<AST::AstType> getFunctionType() const;
        void gen(std::shared_ptr<AST::IASTVisitor> visitor);
    private:
        Token                                 m_funName;
        std::shared_ptr<AST::AstType>         m_type;
        std::shared_ptr<AST::AstAttribute>    m_attribute;
    };
}