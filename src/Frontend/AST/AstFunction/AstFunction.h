#pragma once
#include <vector>
#include <memory>

#include "Frontend/AST/AstTree.h"
#include "Frontend/AST/AstExpr/AstObjectExpr.h"
#include "Frontend/AST/AstStmt/AstStmt.h"
#include "Frontend/AST/AstBlock.h"

#include "Frontend/AST/AstOther/AstType.h"
#include "Frontend/AST/AstOther/AstAttribute.h"
#include "Frontend/AST/AstOther/AstParamList.h"


namespace AST {
    
    class ICollectInfoBack;
    class AstFunction :  public  AstTree{
    public:
        AstFunction( Token name, std::shared_ptr<AstType> type,
                     std::shared_ptr<AST::AstParamList>param, std::shared_ptr<AST::AstBlock> block) 
            : m_funName( name )
            , m_type( type )
            , m_paramList( param )
            , m_functionBody( block )
        {
        }

        Token getFunctionName() const;
        std::shared_ptr<AST::AstType> getFunctionType() const;
        std::shared_ptr<AST::AstParamList> getFunctionParamList() const;
        std::shared_ptr<AST::AstAttribute> getFunctionAttribute() const;
        std::shared_ptr<AST::AstBlock>     getFunctionBlock() const;
        void gen(std::shared_ptr<AST::IASTVisitor> visitor, ICollectInfoBack * collect);
    private:
        Token                                 m_funName;
        std::shared_ptr<AST::AstType>         m_type;
        std::shared_ptr<AST::AstParamList>    m_paramList;
        std::shared_ptr<AST::AstAttribute>    m_attribute;
        std::shared_ptr<AST::AstBlock>        m_functionBody;
    };
}